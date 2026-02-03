%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
","   { return COMMA; }
":"   { return DVOTACKA; }
"%"   { return PERCENT; }
"$"   { return DOLLAR; }
"+"   { return PLUS; }
"*"   { return STAR; }
"["   { return L_BRACKET; }
"]"   { return R_BRACKET; }

"0x"[0-9a-fA-F]+ { yylval.num = strtol(yytext, NULL, 16); return HEX_NUMBER; }
[+-]?[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }

".global"  { return GLOBAL; }
".extern"  { return EXTERN; }
".section" { return SECTION; }
".word"    { return WORD; }
".skip"    { return SKIP; }
".equ"     { return EQU; }
".end"     { return END; }

"halt" { return HALT; }
"int"  { return INT; }
"iret" { return IRET; }
"call" { return CALL; }
"ret"  { return RET; }
"jmp"  { return JMP; }
"jeq"  { return JEQ; }
"jne"  { return JNE; }
"jgt"  { return JGT; }
"push" { return PUSH; }
"pop"  { return POP; }
"xchg" { return XCHG; }
"add"  { return ADD; }
"sub"  { return SUB; }
"mul"  { return MUL; }
"div"  { return DIV; }
"cmp"  { return CMP; }
"not"  { return NOT; }
"and"  { return AND; }
"or"   { return OR; }
"xor"  { return XOR; }
"test" { return TEST; }
"shl"  { return SHL; }
"shr"  { return SHR; }
"ldr"  { return LDR; }
"str"  { return STR; }

"sp"  { return STACK_POINTER; }
"pc"  { return PROGRAM_COUNTER; }
"psw" { return PROGRAM_STATUS_WORD; }


"r"[0-7] { return REGISTER; }

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return SIMBOL;
}

\n      { return EOL; }

[ \t]+   { /* ignore */ }

.        { return yytext[0]; }
%%

int yywrap(void){ return 1; }
