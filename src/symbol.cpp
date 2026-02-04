#include "symbol.h"

// Konstruktor
Simbol::Simbol(int num,
               const std::string& name,
               uint32_t value,
               uint32_t size,
               SymbolType type,
               SymbolBinding bind,
               int ndx)
    : num(num),
      name(name),
      value(value),
      size(size),
      type(type),
      bind(bind),
      ndx(ndx)
{
}
// Konstruktor
Simbol::Simbol()
{
}

// Getteri
int Simbol::getNum() const {
    return num;
}

uint32_t Simbol::getValue() const {
    return value;
}

uint32_t Simbol::getSize() const {
    return size;
}

SymbolType Simbol::getType() const {
    return type;
}

SymbolBinding Simbol::getBind() const {
    return bind;
}

int Simbol::getNdx() const {
    return ndx;
}

std::string Simbol::getName() const {
    return name;
}

// Setteri
void Simbol::setNum(int num) {
    this->num = num;
}

void Simbol::setValue(uint32_t value) {
    this->value = value;
}

void Simbol::setSize(uint32_t size) {
    this->size = size;
}

void Simbol::setType(SymbolType type) {
    this->type = type;
}

void Simbol::setBind(SymbolBinding bind) {
    this->bind = bind;
}

void Simbol::setNdx(int ndx) {
    this->ndx = ndx;
}