#include "dataTable.h"
#include <iostream>
#include <iomanip>

Sekcija* DataTable::absSection = new Sekcija("ABS", 0, 0);

// Privatni konstruktor
DataTable::DataTable() {
    this->prviProlaz=true;
    this->currentSection=nullptr;
    this->locationCounter=0;
}

// Singleton instanca (thread-safe od C++11)
DataTable& DataTable::getInstance() {
    static DataTable instance;
    return instance;
}

void DataTable::addSymbol(Simbol* simbol) {
    if (!simbol) return;
    Simbol* stari = simboli[simbol->getName()];
    if(stari==0){
       simboli[simbol->getName()] = simbol;
    }else{
        if(stari->isExtern() && simbol->getSectionOwner()){
            std::cout << "error\n";
        }
        if(!stari->getSectionOwner() && stari->getValue()==-1){
            simboli[simbol->getName()] = simbol;
            std::cout << "neknadno smo definisali simbol" << simbol->getName()<<"\n";

        }
    }
}

void DataTable::addSection(Sekcija* sekcija) {
    if (!sekcija) return;
    if (sekcije.find(sekcija->getName()) == sekcije.end()) {
        sekcije[sekcija->getName()] = sekcija;
    }
    this->currentSection = sekcija;
}

void DataTable::printTable() {
    std::cout << "================= TABELA SIMBOLA =================" << std::endl;

    std::cout << std::left
              << std::setw(5)  << "Num"
              << std::setw(15) << "Name"
              << std::setw(10) << "Value"
              << std::setw(6)  << "Size"
              << std::setw(6)  << "Ndx"
              << std::setw(12) << "Section"
              << std::setw(12) << "Externi"
              << std::setw(12) << "Globalni"
              << std::endl;

    std::cout << "--------------------------------------------------------------" << std::endl;

    for (const auto& par : simboli) {
        Simbol* s = par.second;
        if (!s) continue;

        std::stringstream val;
        val << "0x" << std::hex << s->getValue();

        std::cout << std::left
                  << std::setw(5)  << s->getNum()
                  << std::setw(15) << s->getName()
                  << std::setw(10) << val.str()
                  << std::setw(6)  << s->getSize()
                  << std::setw(6)  << s->getNdx()
                  << std::setw(12) << (s->getSectionOwner() ? s->getSectionOwner()->getName() : "UND")
                  << std::setw(12) << (s->isExtern() ? "Eksterni" : "Ne")
                  << std::setw(12) << (s->isGlobal() ? "Globalni" : "Ne")
                  << std::endl;
    }

    std::cout << std::endl;
    std::cout << "================= TABELA SEKCIJA =================" << std::endl;
    std::cout << "Name\tBase\tSize" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    for (const auto& par : sekcije) {
        Sekcija* sec = par.second;
        if (!sec) continue;

        std::cout
            << sec->getName() << "\t"
            << std::hex << "0x" << sec->getBase() << std::dec << "\t"
            << sec->getSize()
            << std::endl;
        std::cout<<" sadrzaj \n";
        for (byte b : sec->getByteCode()) {
            int val = static_cast<int>(b);

            if (val < 16) std::cout << "0"; // da dobijes 2 cifre

            std::cout << std::hex << val << " ";
        }
        std::cout<<"\n";
    }

    std::cout << "\n================= RELOKACIONI ZAPISI =================" << std::endl;

    for (const auto& par : sekcije) {
        Sekcija* sec = par.second;
        if (!sec) continue;

        const auto& rels = sec->getRelokacije();
        if (rels.empty()) continue;

        std::cout << "\nRelokacije za sekciju: " << sec->getName() << std::endl;

        std::cout << std::left
                << std::setw(10) << "Offset"
                << std::setw(15) << "Type"
                << std::setw(20) << "Symbol"
                << std::setw(10) << "Addend"
                << std::endl;

        std::cout << "--------------------------------------------------------------" << std::endl;

        for (Relocation* r : rels) {
            if (!r) continue;

            std::stringstream off;
            off << "0x" << std::hex << r->getOffset();

            std::string typeStr =
                (r->getTip() == R_ABS ? "R_ABS" : "R_PC_REL");

            std::cout << std::left
                    << std::setw(10) << off.str()
                    << std::setw(15) << typeStr
                    << std::setw(20) << r->getSimbol()
                    << std::setw(10) << r->getAddend()
                    << std::endl;
        }
    }


}


const std::unordered_map<std::string,Simbol*>& DataTable::getSimboli() const {
    return simboli;
}

// Opciono: oslobodi memoriju ako SI vlasnik simbola
DataTable::~DataTable() {
    
}

Sekcija* DataTable::getCurrentSection() const {
    return currentSection;
}

// setter
void DataTable::setCurrentSection(Sekcija* section) {
    this->currentSection = section;
}

int DataTable::getLocationCounter() const{
    return locationCounter;
}

void DataTable::addLocationCounter(int num){
    locationCounter+=num;
}

bool DataTable::getPrviProlaz() const{
    return prviProlaz;
}

void DataTable::setPrviProlaz(){
    this->prviProlaz=false;
    this->currentSection=nullptr;
    this->locationCounter=0;
}

Sekcija* DataTable::getSectionByName(const std::string& name) {
    auto it = sekcije.find(name);

    if (it == sekcije.end()) {
        return nullptr;
    }

    return it->second;
}