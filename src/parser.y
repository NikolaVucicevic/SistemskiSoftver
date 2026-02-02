%{
#include <stdio.h>
#include <stdlib.h>
#include <firstPass.h>

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
  | lines line {printf("Naisli smo na linije \n");}
;

line:
    direktiva EOL
    |
    labela EOL
    |
    direktiva
    |
    labela
    |
    EOL
;

direktiva:
GLOBAL SIMBOL {printf("Naisli smo na direktivu global"); }
|
SECTION SIMBOL {printf("Naisli smo na direktivu sekcije"); novaSekcija();}
;

labela:
SIMBOL DVOTACKA {printf("Naisli smo na labelu"); }



%%





int yyerror(const char *s){
    printf("Parse error: %s\n", s);
    return 0;
}