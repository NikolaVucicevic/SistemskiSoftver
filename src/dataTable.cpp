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
    simboli.push_back(simbol);
     std::cout << "[DataTable] Dodajem simbol ";
}

const std::vector<Simbol*>& DataTable::getSimboli() const {
    return simboli;
}

// Opciono: oslobodi memoriju ako SI vlasnik simbola
DataTable::~DataTable() {
    for (auto s : simboli)
        delete s;
}