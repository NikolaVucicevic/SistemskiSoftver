#ifndef DATATABLE_H
#define DATATABLE_H

#include "myElf.h"
#include "symbol.h"
#include "section.h"
#include <string>
#include <vector>
#include <unordered_map>

class DataTable {
private:
    std::unordered_map<std::string,Simbol*> simboli;
    std::unordered_map<std::string,Sekcija*> sekcije;
    Sekcija* currentSection;

    bool prviProlaz;
    int locationCounter;
    // Privatni konstruktor
    DataTable();


public:
    //Zabranjeno kopiranje i dodela
    DataTable(const DataTable&) = delete;
    DataTable& operator=(const DataTable&) = delete;

    // Globalna tačka pristupa
    static DataTable& getInstance();

    // Javne metode
    void addSymbol(Simbol* simbol);
    void addSection(Sekcija* sekcija);
    const std::unordered_map<std::string,Simbol*>& getSimboli() const;

    void printTable();

    // (opciono) destruktor
    ~DataTable();
};


#endif