#ifndef SIMBOL_H
#define SIMBOL_H

#include "myElf.h"
#include <string>
#include "section.h"


class Simbol {
private:
    int num;
    uint32_t value;
    uint32_t size;
    SymbolType type;
    SymbolBinding bind;
    int ndx;
    std::string name;
    Sekcija* sectionOwner;

public:
    // konstruktor
    Simbol(int num,
           const std::string& name,
           uint32_t value,
           uint32_t size,
           SymbolType type,
           SymbolBinding bind,
           int ndx,
           Sekcija* sectionOwner);
    Simbol();
    // getteri
    int getNum() const;
    uint32_t getValue() const;
    uint32_t getSize() const;
    SymbolType getType() const;
    SymbolBinding getBind() const;
    int getNdx() const;
    std::string getName() const;
    Sekcija* getSectionOwner() const;

    // setteri
    void setNum(int num);
    void setName(const std::string& name);
    void setValue(uint32_t value);
    void setSize(uint32_t size);
    void setType(SymbolType type);
    void setBind(SymbolBinding bind);
    void setNdx(int ndx);
    void setSectionOwner(Sekcija* section);
};

#endif