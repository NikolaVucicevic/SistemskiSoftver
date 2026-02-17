#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;

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

#ifdef __cplusplus
}
#endif