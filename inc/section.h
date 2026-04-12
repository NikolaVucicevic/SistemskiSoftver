#ifndef SECTION_H
#define SECTION_H

#include "myElf.h"
#include "relocation.h"
#include <string>
#include <vector>

class Sekcija {
private:
    std::string name;
    int base;
    int size;
    std::vector<byte> byteCode;
    int ndx;

    std::vector<Relocation*> relokacije; // ← OVO

public:
    // Konstruktori
    Sekcija();
    Sekcija(const std::string& name, int base, int size);

    // Getteri
    const std::string& getName() const;
    int getBase() const;
    int getSize() const;
    std::vector<byte>& getByteCode();
    int getNdx() const;

    // Setteri
    void setName(const std::string& name);
    void setBase(int base);
    void setSize(int size);
    void addByte(byte b);
    void setNdx(int ndx);

    void addRelocation(Relocation* r);
    const std::vector<Relocation*>& getRelokacije() const;
};

#endif