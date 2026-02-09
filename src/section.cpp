#include "section.h"

// Podrazumevani konstruktor
Sekcija::Sekcija()
    : name(""), base(0), size(0) {}

// Konstruktor sa parametrima
Sekcija::Sekcija(const std::string& name, int base, int size)
    : name(name), base(base), size(size) {}

// Getteri
const std::string& Sekcija::getName() const {
    return name;
}

int Sekcija::getBase() const {
    return base;
}

int Sekcija::getSize() const {
    return size;
}

 std::vector<byte>& Sekcija::getByteCode(){
    return byteCode;
}

// Setteri
void Sekcija::setName(const std::string& name) {
    this->name = name;
}

void Sekcija::setBase(int base) {
    this->base = base;
}

void Sekcija::setSize(int size) {
    this->size = size;
}

void Sekcija::addByte(byte b) {
    this->byteCode.push_back(b);
}