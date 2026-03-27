#ifndef WRAPPER_H
#define WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;

typedef enum {
    IMMEDIATE,
    REG_DIR,
    REG_IND,
    REG_IND_OFF,
    MEM_DIR
} AddrMode;

typedef struct {
    AddrMode mode;
    int reg;
    int literal;
    char* simbol;
    int imaPayload;
} Operand;

void novaSekcija_c();

void dodajSekciju_f(const char* s);
void ispisiTabelu_fs();

void dodajSimbolUnd(const char* s);
void dodajSimbolEqu(const char* s,int num);
void dodajSimbolExt(const char* s);
void dodajSimbolGlob(const char* s);
void dodajSimbolLabela(const char* s);

void addToCounter_f(int num);
void endUpdates();


void dodajBajt(byte broj);
void dodajWordSimbol_s(const char* s,int offs);

void upisiHALT();
void upisiIRET();
void upisiRET();

void upisiINT(int reg);

void upisiCALL(Operand* operand);
void upisiJMP(Operand* operand);
void upisiJEQ(Operand* operand);
void upisiJNE(Operand* operand);
void upisiJGT(Operand* operand);

void upisiPUSH(int reg);
void upisiPOP(int reg);

void upisiXCHG(int r1, int r2);

void upisiADD(int r1, int r2);
void upisiSUB(int r1, int r2);
void upisiMUL(int r1, int r2);
void upisiDIV(int r1, int r2);
void upisiCMP(int r1, int r2);

void upisiNOT(int reg);

void upisiAND(int r1, int r2);
void upisiOR(int r1, int r2);
void upisiXOR(int r1, int r2);
void upisiTEST(int r1, int r2);

void upisiSHL(int r1, int r2);
void upisiSHR(int r1, int r2);

void upisiLDR(int reg, Operand* operand);
void upisiSTR(int reg, Operand* op);

#ifdef __cplusplus
}
#endif

#endif