#include "dataTable.h"
#include <iostream>

// Privatni konstruktor
DataTable::DataTable() {}

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

void DataTable::printTable() {
    std::cout << "=== Tabela simbola ===" << std::endl;

    for (const auto& par : simboli) {
        std::cout << par.first << std::endl;
    }
}

const std::unordered_map<std::string,Simbol*>& DataTable::getSimboli() const {
    return simboli;
}

// Opciono: oslobodi memoriju ako SI vlasnik simbola
DataTable::~DataTable() {
    
}