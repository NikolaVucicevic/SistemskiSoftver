#include "section.h"

// Podrazumevani konstruktor
Sekcija::Sekcija()
    : name(""), base(0), size(0) {}

// Konstruktor sa parametrima
Sekcija::Sekcija(const std::string& name, uint64_t base, uint64_t size)
    : name(name), base(base), size(size) {}

// Getteri
const std::string& Sekcija::getName() const {
    return name;
}

uint64_t Sekcija::getBase() const {
    return base;
}

uint64_t Sekcija::getSize() const {
    return size;
}

// Setteri
void Sekcija::setName(const std::string& name) {
    this->name = name;
}

void Sekcija::setBase(uint64_t base) {
    this->base = base;
}

void Sekcija::setSize(uint64_t size) {
    this->size = size;
}
