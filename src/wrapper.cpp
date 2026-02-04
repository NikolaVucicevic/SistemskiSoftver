#include "wrapper.h"
#include "firstPass.h"


void novaSekcija_c() { novaSekcija(); }

void dodajSimbol_c(const char* s) {
    Simbol* s1= new Simbol();
    DataTable::getInstance().addSymbol(s1);
}