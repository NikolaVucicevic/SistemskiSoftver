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
    SymbolBinding bind;
    int ndx;
    std::string name;
    Sekcija* sectionOwner;
    bool externi;

public:
    // konstruktor
    Simbol(int num,
           const std::string& name,
           uint32_t value,
           uint32_t size,
           SymbolBinding bind,
           int ndx,
           Sekcija* sectionOwner,
            bool externi);
    Simbol();
    // getteri
    int getNum() const;
    uint32_t getValue() const;
    uint32_t getSize() const;
    SymbolBinding getBind() const;
    int getNdx() const;
    std::string getName() const;
    Sekcija* getSectionOwner() const;
    bool isExtern() const;

    // setteri
    void setNum(int num);
    void setName(const std::string& name);
    void setValue(uint32_t value);
    void setSize(uint32_t size);
    void setBind(SymbolBinding bind);
    void setNdx(int ndx);
    void setSectionOwner(Sekcija* section);
    void setExtern(bool externi);

};

#endif