#ifndef SIMBOL_H
#define SIMBOL_H

#include "myElf.h"
#include <string>


class Simbol {
private:
    int num;
    uint32_t value;
    uint32_t size;
    SymbolType type;
    SymbolBinding bind;
    int ndx;
    std::string name;

public:
    // konstruktor
    Simbol(int num,
           const std::string& name,
           uint32_t value,
           uint32_t size,
           SymbolType type,
           SymbolBinding bind,
           int ndx);

    // getteri
    int getNum() const;
    uint32_t getValue() const;
    uint32_t getSize() const;
    SymbolType getType() const;
    SymbolBinding getBind() const;
    int getNdx() const;
    std::string getName() const;

    // setteri
    void setValue(uint32_t value);
    void setSize(uint32_t size);
    void setType(SymbolType type);
    void setBind(SymbolBinding bind);
    void setNdx(int ndx);
};

#endif