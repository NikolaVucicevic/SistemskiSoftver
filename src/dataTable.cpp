#include "dataTable.h"
#include <iostream>

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
    if(simboli[simbol->getName()]==0){
       simboli[simbol->getName()] =simbol;
    }
     std::cout << "[DataTable] Dodajem simbol ";
}

void DataTable::addSection(Sekcija* sekcija) {
    if (!sekcija) return;
    if(sekcije[sekcija->getName()]==0){
       sekcije[sekcija->getName()] = sekcija;
    }
    this->currentSection = sekcija;
    this->locationCounter=0;
     std::cout << "[DataTable] Dodajemo sekciju ";
}

void DataTable::printTable() {
    std::cout << "================= TABELA SIMBOLA =================" << std::endl;
    std::cout << "Num\tName\t\tValue\tSize\tType\tBind\tNdx\tSection" << std::endl;
    std::cout << "--------------------------------------------------" << std::endl;

    for (const auto& par : simboli) {
        Simbol* s = par.second;
        if (!s) continue;

        std::cout
            << s->getNum() << "\t"
            << s->getName() << "\t\t"
            << std::hex << "0x" << s->getValue() << std::dec << "\t"
            << s->getSize() << "\t"
            << static_cast<int>(s->getType()) << "\t"
            << static_cast<int>(s->getBind()) << "\t"
            << s->getNdx() << "\t";

        if (s->getSectionOwner())
            std::cout << s->getSectionOwner()->getName();
        else
            std::cout << "UND";

        std::cout << std::endl;
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
