#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.tab.h"
#include <dataTable.h>

extern int yylex();
extern FILE* yyin;
extern void yyrestart(FILE*);

int main() {

    const char* inputFile = "tests/test.s";

    printf("ULAZIM U PARSER1\n");
    yyin = fopen(inputFile, "r");

    yyparse();
    fclose(yyin);
    printf("IZLAZIM IZ PARSER1\n");

    DataTable::getInstance().setPrviProlaz();

    printf("ULAZIM U PARSER2\n");
    yyin = fopen(inputFile, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    printf("IZLAZIM IZ PARSER2\n");

    
    FILE *fileHandle = fopen("generated.o", "wb");
    char str[] = "hello world\n";
    fwrite(str, 1, strlen(str), fileHandle);
    return 0;
}