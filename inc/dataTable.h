#ifndef DATATABLE_H
#define DATATABLE_H

#include "myElf.h"
#include "symbol.h"
#include <string>
#include <vector>

class DataTable {
private:
    std::vector<Simbol*> simboli;

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
    const std::vector<Simbol*>& getSimboli() const;

    // (opciono) destruktor
    ~DataTable();
};


#endif