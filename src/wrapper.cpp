#include "wrapper.h"
#include "dataTable.h"



void dodajSimbol_c(const char* s) {
    Simbol* s1= new Simbol();
    s1->setName(s);
    DataTable::getInstance().addSymbol(s1);
}

void ispisiTabelu_fs(){
    DataTable::getInstance().printTable();
}

void dodajSekciju_f(const char* s){
    //znaci samo u prvom prolazu
    Sekcija* s1= new Sekcija();
    s1->setName(s);
    DataTable::getInstance().addSection(s1);
}


