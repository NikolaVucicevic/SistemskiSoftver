#include "relocation.h"

// Konstruktor
Relocation::Relocation(int offset, TipRelokacije tip,
                       const std::string& simbol, int addend)
    : offset(offset), tip(tip), simbol(simbol), addend(addend)
{
}

// Getteri

int Relocation::getOffset() const {
    return offset;
}

TipRelokacije Relocation::getTip() const {
    return tip;
}

std::string Relocation::getSimbol() const {
    return simbol;
}

int Relocation::getAddend() const {
    return addend;
}