#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.tab.h"

extern int yylex();

int main() {
    printf("ULAZIM U PARSER\n");
    yyparse();
    printf("IZLAZIM IZ PARSER\n");
    FILE *fileHandle = fopen("generated.o", "wb");
    char str[] = "hello world\n";
    fwrite(str, 1, strlen(str), fileHandle);
    return 0;
}