#include "symbol.h"

// Konstruktor
Simbol::Simbol(int num,
               const std::string& name,
               uint32_t value,
               uint32_t size,
               SymbolBinding bind,
               int ndx,
                Sekcija* sectionOwner,
                bool externi
            )
    : num(num),
      name(name),
      value(value),
      size(size),
      bind(bind),
      ndx(ndx),
      sectionOwner(sectionOwner),
      externi(externi)
{
}
// Konstruktor
Simbol::Simbol()
{
    this->value=-1;
    this->sectionOwner = nullptr;
    this->externi = false;
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

SymbolBinding Simbol::getBind() const {
    return bind;
}

int Simbol::getNdx() const {
    return ndx;
}

std::string Simbol::getName() const {
    return name;
}

Sekcija* Simbol::getSectionOwner() const {
    return sectionOwner;
}

bool Simbol::isExtern() const{
    return externi;
}

// Setteri
void Simbol::setNum(int num) {
    this->num = num;
}

void Simbol::setName(const std::string& name) {
    this->name = name;
}

void Simbol::setValue(uint32_t value) {
    this->value = value;
}

void Simbol::setSize(uint32_t size) {
    this->size = size;
}

void Simbol::setBind(SymbolBinding bind) {
    this->bind = bind;
}

void Simbol::setNdx(int ndx) {
    this->ndx = ndx;
}

void Simbol::setSectionOwner(Sekcija* section) {
    this->sectionOwner = section;
}

void Simbol::setExtern(bool externi) {
    this->externi = externi;
}