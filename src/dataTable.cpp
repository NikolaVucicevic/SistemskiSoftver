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
    if(simboli[simbol->getName()]!=0){
       simboli[simbol->getName()] =simbol;
    }
     std::cout << "[DataTable] Dodajem simbol ";
}

void DataTable::addSection(Sekcija* sekcija) {
    if (!sekcija) return;
    if(sekcije[sekcija->getName()]!=0){
       sekcije[sekcija->getName()] = sekcija;
    }
    this->currentSection = sekcija;
    this->locationCounter=0;
     std::cout << "[DataTable] Dodajemo sekciju ";
}

void DataTable::printTable() {
    std::cout << "=== Tabela simbola ===" << std::endl;

    for (const auto& par : simboli) {
        std::cout << par.first << std::endl;
    }
    std::cout << "=== Tabela sekcija ===" << std::endl;

    for (const auto& par : sekcije) {
        std::cout << par.first << std::endl;
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
