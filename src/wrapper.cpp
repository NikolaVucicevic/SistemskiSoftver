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
    Sekcija* sek1= new Sekcija();
    sek1->setName(s);
    DataTable::getInstance().addSection(sek1);
    DataTable::getInstance().setCurrentSection(sek1);


    Simbol* s1 = new Simbol();
    s1->setName(s);
    s1->setValue(0);
    s1->setSectionOwner(DataTable::getInstance().getCurrentSection());
    //dodaj da je u apsolutnoj sekciji
    DataTable::getInstance().addSymbol(s1);

    


}

void dodajSimbolEqu(const char* s,int num){
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(num);
    s1->setSectionOwner(DataTable::getInstance().getCurrentSection());
    //dodaj da je u apsolutnoj sekciji
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolExt(const char* s){
    Simbol* s1= new Simbol();
    s1->setName(s);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolNaredba(const char* s){
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(DataTable::getInstance().getLocationCounter());
    s1->setSectionOwner(DataTable::getInstance().getCurrentSection());
    //dodaj da je u apsolutnoj sekciji
    DataTable::getInstance().addSymbol(s1);
}


