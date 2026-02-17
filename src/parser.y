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
    lines {  }
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
    SIMBOL DVOTACKA {  dodajSimbolLabela($1); }
;

stmt_opt:
    /* prazno */
  | direktiva
  | naredba
;

direktiva:
    GLOBAL simboli {
        for (int i = 0; i < simboli_len; i++){
            dodajSimbolGlob($2[i]);
            free($2[i]);
        } 
        free($2);
    }
  |
    EXTERN simboli {

        for (int i = 0; i < simboli_len; i++) {
            dodajSimbolExt($2[i]);
            free($2[i]);
        }
        free($2);
    }
  |
    SECTION SIMBOL {
        dodajSekciju_f($2);
    }
  |
    WORD simboli {

        addToCounter_f(simboli_len * 2);

        for (int i = 0; i < simboli_len; i++) {
            dodajSimbolUnd($2[i]);
            dodajWordSimbol_s($2[i],i*2);
            free($2[i]);
        }
        free($2);
    }
  |
    WORD NUMBER {
        int val = $2;

        dodajBajt(val & 0xFF);
        dodajBajt((val >> 8) & 0xFF);
        printf("dodajmo broj word %d\n", val);

        addToCounter_f($2);
    }
  |
    SKIP NUMBER {
        addToCounter_f($2);
        for(int i=0;i<$2;i++){
            dodajBajt(0);
        }
    }
  |
    EQU SIMBOL COMMA NUMBER {
        dodajSimbolEqu($2, $4);
    }
  |
    END {
        endUpdates();
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

    }
  |
    simboli COMMA SIMBOL {
        simboli_len++;
        $$ = (char**)realloc($1, (size_t)simboli_len * sizeof(char*));
        if (!$$) { perror("realloc"); exit(1); }

        $$[simboli_len - 1] = strdup($3);
        if (!$$[simboli_len - 1]) { perror("strdup"); exit(1); }

    }
;

naredba:
    HALT { upisiHALT(); }
  |
    IRET { upisiIRET(); }
  |
    RET { upisiRET(); }
  |
    LDR REGISTER COMMA operand
;

operand:
    DOLLAR SIMBOL { dodajSimbolUnd($2); }
  |
    SIMBOL { dodajSimbolUnd($1); }
;

%%

int yyerror(const char *s){
    printf("Parse error: %s\n", s);
    return 0;
}
