#include "wrapper.h"
#include "dataTable.h"



void dodajSimbolUnd(const char* s) {
    Simbol* s1= new Simbol();
    s1->setName(s);
    DataTable::getInstance().addSymbol(s1);
}

void ispisiTabelu_fs(){
    DataTable::getInstance().printTable();
}

void dodajSekciju_f(const char* s){
    DataTable& dt = DataTable::getInstance();

    // 1. Ako postoji prethodna sekcija — zatvori je
    Sekcija* prev = dt.getCurrentSection();
    if (prev != nullptr) {
        prev->setSize(
            dt.getLocationCounter() - prev->getBase()
        );
    }

    // 2. Napravi novu sekciju
    Sekcija* sek1 = new Sekcija();
    sek1->setName(s);

    sek1->setBase(dt.getLocationCounter());

    dt.addSection(sek1);

    dt.setCurrentSection(sek1);


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
    //ovde treba absolute section
    s1->setSectionOwner(DataTable::getInstance().getCurrentSection());
    //dodaj da je u apsolutnoj sekciji
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolExt(const char* s){
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(0);
    s1->setExtern(true);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolGlob(const char* s){
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(0);
    s1->setGlobal(true);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolLabela(const char* s){
    Simbol* s1 = new Simbol();
    s1->setName(s);

    DataTable& dt = DataTable::getInstance();
    Sekcija* cur = dt.getCurrentSection();

    s1->setValue(dt.getLocationCounter() - cur->getBase());
    s1->setSectionOwner(cur);

    dt.addSymbol(s1);
}

void addToCounter_f(int num){
    DataTable::getInstance().addLocationCounter(num);
}

void endUpdates(){
    DataTable& dt = DataTable::getInstance();

    // 1. Ako postoji prethodna sekcija — zatvori je
    Sekcija* prev = dt.getCurrentSection();
    if (prev != nullptr) {
        prev->setSize(
            dt.getLocationCounter() - prev->getBase()
        );
    }
}



//drugi prolaz

void dodajBajt(byte broj){
    DataTable::getInstance().getCurrentSection()->addByte(broj);
}

