#include "wrapper.h"
#include "firstPass.h"


void novaSekcija_c() { novaSekcija(); }

void dodajSimbol_c(const char* s) {
    Simbol* s1= new Simbol();
    s1->setName(s);
    DataTable::getInstance().addSymbol(s1);
}

void ispisiTabelu(){
    DataTable::getInstance().printTable();
}

void dodajSekciju_f(const char* s){
    
}
