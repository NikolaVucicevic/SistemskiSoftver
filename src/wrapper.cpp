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
        if(sym->getSectionOwner()==dt.absSection){
            int val = sym->getValue();
            dodajBajt(val & 0xFF);
            dodajBajt((val >> 8) & 0xFF);
        }else if(sym->getSectionOwner()==dt.getCurrentSection()){
            //mozemo samo value od simbola da ubacimo u kod
            int val = sym->getValue();
            dodajBajt(val & 0xFF);
            dodajBajt((val >> 8) & 0xFF);
        }else{
            dodajBajt(0);
            dodajBajt(0);

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

void upisiCALL(Operand* operand) {}

void upisiJMP(Operand* operand) {}

void upisiJEQ(Operand* operand) {}

void upisiJNE(Operand* operand) {}

void upisiJGT(Operand* operand) {}

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

    if (DataTable::getInstance().getPrviProlaz()) {
        return;
    }

    auto sekcija = DataTable::getInstance().getCurrentSection();

    uint8_t byte1 = 0b01100000; // 0x60
    uint8_t byte2 = ((r1 & 0xF) << 4) | (r2 & 0xF);

    sekcija->addByte(byte1);
    sekcija->addByte(byte2);
}

//------------Instrukcije aritmetickih operacija-----------

void upisiAritInstr(uint8_t mmmm, int r1, int r2) {
    addToCounter_f(2);

    if (DataTable::getInstance().getPrviProlaz()) {
        return;
    }

    auto sekcija = DataTable::getInstance().getCurrentSection();

    uint8_t byte1 = (0b0111 << 4) | (mmmm & 0xF);
    uint8_t byte2 = ((r1 & 0xF) << 4) | (r2 & 0xF);

    sekcija->addByte(byte1);
    sekcija->addByte(byte2);
}

void upisiADD(int r1, int r2) {
    upisiAritInstr(0b0000, r1, r2);
}

void upisiSUB(int r1, int r2) {
    upisiAritInstr(0b0001, r1, r2);
}

void upisiMUL(int r1, int r2) {
    upisiAritInstr(0b0010, r1, r2);
}

void upisiDIV(int r1, int r2) {
    upisiAritInstr(0b0011, r1, r2);
}

void upisiCMP(int r1, int r2) {
    upisiAritInstr(0b0100, r1, r2);
}

//------------Instrukcije logickih operacija-----------

void upisiLogInstr(uint8_t mmmm, int r1, int r2) {
    addToCounter_f(2);

    if (DataTable::getInstance().getPrviProlaz()) {
        return;
    }

    auto sekcija = DataTable::getInstance().getCurrentSection();

    uint8_t byte1 = (0b1000 << 4) | (mmmm & 0xF);
    uint8_t byte2 = ((r1 & 0xF) << 4) | (r2 & 0xF);

    sekcija->addByte(byte1);
    sekcija->addByte(byte2);
}


void upisiNOT(int r1) {
    upisiLogInstr(0b0000, r1, 0); // SSSS = 0
}

void upisiAND(int r1, int r2) {
    upisiLogInstr(0b0001, r1, r2);
}

void upisiOR(int r1, int r2) {
    upisiLogInstr(0b0010, r1, r2);
}

void upisiXOR(int r1, int r2) {
    upisiLogInstr(0b0011, r1, r2);
}

void upisiTEST(int r1, int r2) {
    upisiLogInstr(0b0100, r1, r2);
}

//------------Instrukcije pomerackih operacija-----------

void upisiShiftInstr(uint8_t mmmm, int r1, int r2) {
    addToCounter_f(2);

    if (DataTable::getInstance().getPrviProlaz()) {
        return;
    }

    auto sekcija = DataTable::getInstance().getCurrentSection();

    uint8_t byte1 = (0b1001 << 4) | (mmmm & 0xF);
    uint8_t byte2 = ((r1 & 0xF) << 4) | (r2 & 0xF);

    sekcija->addByte(byte1);
    sekcija->addByte(byte2);
}

void upisiSHL(int r1, int r2) {
    upisiShiftInstr(0b0000, r1, r2);
}

void upisiSHR(int r1, int r2) {
    upisiShiftInstr(0b0001, r1, r2);
}




void upisiLDR(int reg, Operand* operand) {}

void upisiSTR(int reg, Operand* op) {
/*
    if (op->mode == REG_IND_OFF || op->mode == MEM_DIR){
            addToCounter_f(5);
    }else{
        addToCounter_f(3);
    }
    if (DataTable::getInstance().getPrviProlaz()) {
        return;
    }

    uint8_t byte1 = 0b10110000;

    uint8_t byte2 = (reg << 4);

    uint8_t byte3 = 0;

    switch(op->mode) {

        case IMMEDIATE:
            // 0b0000
            throw std::runtime_error("STR ne podrzava immediate adresiranje");
            //ovo ne moze sa store treba error
            break;

        case REG_DIR:
            // 0b0001
            byte2 |= op->reg; // SSSS
            byte3 = 0b00000001;
            break;

        case REG_IND:
            // 0b0010
            byte2 |= op->reg; // SSSS
            byte3 = 0b00000010;
            break;

        case REG_IND_OFF:
            // 0b0011
            byte2 |= op->reg; // SSSS
            byte3 = 0b00000011;
            break;

        case MEM_DIR:
            // 0b0100
            byte3 = 0b00000100;
            break;
    }

    auto sekcija = DataTable::getInstance().getCurrentSection();

    if (sekcija == nullptr) {
        throw std::runtime_error("Nije definisana sekcija ");
    }

    sekcija->addByte(byte1);
    sekcija->addByte(byte2);
    sekcija->addByte(byte3);

    if (op->mode == REG_IND_OFF || op->mode == MEM_DIR) {
        if (op->simbol != nullptr) {
            // imamo simbol
            auto& simboli = DataTable::getInstance().getSimboli();

            auto it = simboli.find(std::string(op->simbol));

            if (it == simboli.end()) {
                throw std::runtime_error("Simbol ne postoji");
            }


            Simbol* sym = it->second;

            

            if(sym->getSectionOwner()==DataTable::getInstance().absSection){
                int val = sym->getValue();

                sekcija->addByte(val & 0xFF);
                sekcija->addByte((val >> 8) & 0xFF);
            }else{
                sekcija->addByte(0);
                sekcija->addByte(0);
                //ovde treba relokacioni zapisi da se dodaju
            }

        }else{
            sekcija->addByte(op->literal & 0xFF);
            sekcija->addByte((op->literal >> 8) & 0xFF);
        }
    }

*/

}