#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.tab.h"

extern int yylex();

int main() {
    printf("ULAZIM U PARSER1\n");
    yyparse();
    printf("IZLAZIM IZ PARSER1\n");
    printf("ULAZIM U PARSER2\n");
    yyparse();
    printf("IZLAZIM IZ PARSER2\n");

    
    FILE *fileHandle = fopen("generated.o", "wb");
    char str[] = "hello world\n";
    fwrite(str, 1, strlen(str), fileHandle);
    return 0;
}