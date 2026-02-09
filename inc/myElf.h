#ifndef MYELF_H
#define MYELF_H

using byte = unsigned char;

typedef enum {
    SYM_LOCAL = 0,
    SYM_GLOBAL = 1,
    SYM_WEAK = 2
} SymbolBinding;

typedef enum {
    SYM_NOTYPE = 0,
    SYM_OBJECT = 1,
    SYM_FUNC   = 2,
    SYM_SECTION= 3,
    SYM_FILE   = 4,
    SYM_COMMON = 5
} SymbolType;


#endif