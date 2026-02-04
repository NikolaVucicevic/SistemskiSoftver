#ifndef SECTION_H
#define SECTION_H

#include "myElf.h"
#include <string>


class Sekcija {
private:
    std::string name;
    uint64_t base;
    uint64_t size;

public:
    // Konstruktori
    Sekcija();
    Sekcija(const std::string& name, uint64_t base, uint64_t size);

    // Getteri
    const std::string& getName() const;
    uint64_t getBase() const;
    uint64_t getSize() const;

    // Setteri
    void setName(const std::string& name);
    void setBase(uint64_t base);
    void setSize(uint64_t size);
};

#endif