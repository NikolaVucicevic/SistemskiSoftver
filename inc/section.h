#ifndef SECTION_H
#define SECTION_H

#include "myElf.h"
#include <string>


class Sekcija {
private:
    std::string name;
    int base;
    int size;

public:
    // Konstruktori
    Sekcija();
    Sekcija(const std::string& name, int base, int size);

    // Getteri
    const std::string& getName() const;
    int getBase() const;
    int getSize() const;

    // Setteri
    void setName(const std::string& name);
    void setBase(int base);
    void setSize(int size);
};

#endif