#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;

void novaSekcija_c();
void dodajSimbolUnd(const char* s);
void dodajSekciju_f(const char* s);
void ispisiTabelu_fs();
void dodajSimbolEqu(const char* s,int num);
void dodajSimbolExt(const char* s);
void dodajSimbolGlob(const char* s);
void dodajSimbolLabela(const char* s);
void addToCounter_f(int num);
void endUpdates();
void dodajBajt(byte broj);
void dodajWordSimbol(const char* s);

#ifdef __cplusplus
}
#endif