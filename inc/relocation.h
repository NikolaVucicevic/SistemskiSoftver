#ifndef RELOCATION_H
#define RELOCATION_H

#include "myElf.h"
#include <string>

enum TipRelokacije {
    R_ABS,
    R_PC_REL
};

class Relocation {
private:
    int offset;              // gde u sekciji
    TipRelokacije tip;       // tip relokacije
    std::string simbol;      // ime simbola
    int addend;              // dodatak

public:
    Relocation(int offset, TipRelokacije tip,
                     const std::string& simbol, int addend);

    int getOffset() const;
    TipRelokacije getTip() const;
    std::string getSimbol() const;
    int getAddend() const;
};

#endif