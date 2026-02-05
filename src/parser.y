%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wrapper.h"

int yylex();
int yyerror(const char *s);

/* globalno: dužina poslednje napravljene liste SIMBOL-a */
static int simboli_len = 0;
%}

%union {
    int num;
    char* str;
    char** strlist;   /* dinamički niz char* */
}

/* tokeni */
%token COMMA DVOTACKA PERCENT DOLLAR EOL
%token PLUS STAR L_BRACKET R_BRACKET
%token<num> HEX_NUMBER NUMBER
%token GLOBAL EXTERN SECTION WORD SKIP EQU END
%token HALT INT IRET CALL RET JMP JEQ JNE JGT
%token PUSH POP XCHG ADD SUB MUL DIV CMP NOT
%token AND OR XOR TEST SHL SHR LDR STR
%token STACK_POINTER PROGRAM_COUNTER PROGRAM_STATUS_WORD
%token REGISTER
%token<str> SIMBOL

%type <strlist> simboli

%%

input:
    lines { printf("Naisli smo na liniju \n"); }
;

lines:
    /* empty */
  | lines line { }
;

line:
    labels stmt_opt EOL
;

labels:
    /* prazno */
  | labels labela
;

labela:
    SIMBOL DVOTACKA
;

stmt_opt:
    /* prazno */
  | direktiva
  | naredba
;

direktiva:
    GLOBAL simboli {
        printf("Naisli smo na direktivu global\n");
        /* ako želiš, obradi simbole isto kao extern/word */
        for (int i = 0; i < simboli_len; i++) free($2[i]);
        free($2);
    }
  |
    EXTERN simboli {
        printf("Naisli smo na direktivu extern\n");

        for (int i = 0; i < simboli_len; i++) {
            dodajSimbol_c($2[i]);
            free($2[i]);
        }
        free($2);
    }
  |
    SECTION SIMBOL {
        printf("Naisli smo na direktivu sekcije\n");
        dodajSekciju_f($2);
    }
  |
    WORD simboli {
        printf("Naisli smo na direktivu word simboli\n");

        addToCounter_f(simboli_len * 2);

        for (int i = 0; i < simboli_len; i++) {
            dodajSimbol_c($2[i]);
            free($2[i]);
        }
        free($2);
    }
  |
    WORD NUMBER {
        printf("Naisli smo na direktivu word\n");
        addToCounter_f($2);
    }
  |
    SKIP NUMBER {
        printf("Naisli smo na direktivu skip\n");
        addToCounter_f($2);
    }
  |
    EQU SIMBOL COMMA NUMBER {
        printf("Naisli smo na direktivu equ\n");
        dodajSimbolEqu($2, $4);
    }
  |
    END {
        printf("Naisli smo na direktivu end\n");
        ispisiTabelu_fs();
    }
;

simboli:
    SIMBOL {
        simboli_len = 1;
        $$ = (char**)malloc(sizeof(char*));
        if (!$$) { perror("malloc"); exit(1); }

        $$[0] = strdup($1);
        if (!$$[0]) { perror("strdup"); exit(1); }

        /* ako flex već radi strdup, može free($1); (po potrebi) */
    }
  |
    simboli COMMA SIMBOL {
        /* $1 je već niz, samo ga proširi */
        simboli_len++;
        $$ = (char**)realloc($1, (size_t)simboli_len * sizeof(char*));
        if (!$$) { perror("realloc"); exit(1); }

        $$[simboli_len - 1] = strdup($3);
        if (!$$[simboli_len - 1]) { perror("strdup"); exit(1); }

        /* ako flex već radi strdup, može free($3); (po potrebi) */
    }
;

naredba:
    HALT
  |
    IRET
  |
    RET
  |
    LDR REGISTER COMMA operand
;

operand:
    DOLLAR SIMBOL { dodajSimbolNaredba($2); }
  |
    SIMBOL { dodajSimbolNaredba($1); }
;

%%

int yyerror(const char *s){
    printf("Parse error: %s\n", s);
    return 0;
}
