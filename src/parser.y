%{
#include <stdio.h>
#include <stdlib.h>
#include <wrapper.h>

int yylex();
int yyerror(const char *s);
%}


%union {
    int num;
    char* str;
}

/* tokeni koje dolaze iz flex-a */
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




%%

input:
    lines {printf("Naisli smo na liniju \n");}
;

lines:
    /* empty */
  | lines line {}
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
GLOBAL simboli {printf("Naisli smo na direktivu global\n"); }
|
EXTERN simboli {printf("Naisli smo na direktivu extern\n"); }
|
SECTION simboli {printf("Naisli smo na direktivu sekcije\n"); novaSekcija_c();}
|
WORD simboli {printf("Naisli smo na direktivu word\n"); }
|
WORD NUMBER {printf("Naisli smo na direktivu word\n"); }
|
SKIP NUMBER {printf("Naisli smo na direktivu skip\n"); }
|
EQU simboli COMMA NUMBER {printf("Naisli smo na direktivu equ\n"); }
|
END {printf("Naisli smo na direktivu end\n"); }
;


simboli:
    SIMBOL { dodajSimbol_c($1) ;}
  | simboli COMMA SIMBOL { dodajSimbol_c($3); }
;



naredba:
    HALT 
    |
    IRET
    |
    RET;



%%





int yyerror(const char *s){
    printf("Parse error: %s\n", s);
    return 0;
}