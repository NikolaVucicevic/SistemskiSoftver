#include "wrapper.h"
#include "dataTable.h"

#include <iostream>





void ispisiTabelu_fs(){
    DataTable::getInstance().printTable();
}

void dodajSekciju_f(const char* s){
    DataTable& dt = DataTable::getInstance();
    if(!dt.getPrviProlaz()){
        //drugi prolaz
        Sekcija* sek = dt.getSectionByName(s);

        if(sek == nullptr){
            printf("GRESKA: sekcija %s ne postoji u drugom prolazu\n", s);
            exit(1);
        }

        dt.setCurrentSection(sek);
        return;
    }

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

void dodajSimbolUnd(const char* s) {
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
    Simbol* s1= new Simbol();
    s1->setName(s);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolEqu(const char* s,int num){
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(num);
    s1->setSectionOwner(DataTable::getInstance().absSection);
    //ovde treba absolute section
    //s1->setSectionOwner(DataTable::getInstance().getCurrentSection());
    //dodaj da je u apsolutnoj sekciji
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolExt(const char* s){
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(0);
    s1->setExtern(true);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolGlob(const char* s){
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
    Simbol* s1= new Simbol();
    s1->setName(s);
    s1->setValue(0);
    s1->setGlobal(true);
    DataTable::getInstance().addSymbol(s1);
}

void dodajSimbolLabela(const char* s){
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
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
    if(!DataTable::getInstance().getPrviProlaz()){
        return;
    }
    DataTable& dt = DataTable::getInstance();

    // 1. Ako postoji prethodna sekcija — zatvori je
    Sekcija* prev = dt.getCurrentSection();
    if (prev != nullptr) {
        prev->setSize(
            dt.getLocationCounter() - prev->getBase()
        );
    }
    //dt.setPrviProlaz();
}



//drugi prolaz

void dodajBajt(byte broj){
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
    DataTable::getInstance().getCurrentSection()->addByte(broj);
}

void dodajWordSimbol_s(const char* s,int offs){
    //if second pass
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }

    DataTable& dt = DataTable::getInstance();

    const auto& simboli = dt.getSimboli();

    auto it = simboli.find(std::string(s));

    if(it != simboli.end()){
        Simbol* sym = it->second;
        if(sym->getSectionOwner()==dt.getCurrentSection()){
            //mozemo samo value od simbola da ubacimo u kod
        }else{
            //moramo da napravimo relokacioni zapis
        }

    }
}


void upisiHALT(){
    addToCounter_f(1);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
    
    DataTable::getInstance().getCurrentSection()->addByte(0);
    
}

void upisiIRET(){
    addToCounter_f(1);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
    DataTable::getInstance().getCurrentSection()->addByte(0x20);
    
}

void upisiRET(){
    addToCounter_f(1);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
    DataTable::getInstance().getCurrentSection()->addByte(0x40);
    
}

void upisiINT(int reg) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiCALL(auto operand) {}

void upisiJMP(auto operand) {}

void upisiJEQ(auto operand) {}

void upisiJNE(auto operand) {}

void upisiJGT(auto operand) {}

void upisiPUSH(int reg) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiPOP(int reg) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiXCHG(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiADD(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiSUB(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiMUL(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiDIV(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiCMP(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiNOT(int reg) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiAND(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiOR(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiXOR(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiTEST(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiSHL(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiSHR(int r1, int r2) {
    addToCounter_f(2);
    if(DataTable::getInstance().getPrviProlaz()){
        return;
    }
}

void upisiLDR(int reg, auto operand) {}

void upisiSTR(int reg, auto operand) {}