#include <elf.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "parser.tab.h"
#include <dataTable.h>
#include <iomanip>
#include <cstring>


#define STRTAB        \
    "\0message_lenbr"   \
    "\0message_end"   \
    "\0message_start" \
    "\0custom_entry"  \
    "\0"

#define SHSTRTAB      \
    "\0.text"         \
    "\0.rela.text"    \
    "\0.data"         \
    "\0.bss"          \
    "\0.symtab"       \
    "\0.strtab"       \
    "\0.shstrtab"     \
    "\0"

#define OFFSET(base, field) ((size_t)((char*)&(field) - (char*)&(base)))

int getOffset(const char *needle, const char *haystack, int haystackLen)
{
    int needleLen = (int)strlen(needle);
    const char *search = haystack;
    int searchLen = haystackLen - needleLen + 1;

    for (; searchLen-- > 0; search++)
    {
        if (!memcmp(search, needle, needleLen))
        {
            return (int)(search - haystack);
        }
    }
    return 0;
}

enum
{
    SECTION_SIZE_TEXT = 46,
    SECTION_SIZE_DATA = 14,
    SECTION_SIZE_BSS = 0,
    SECTION_SIZE_STRTAB = 54,
    SECTION_SIZE_SHSTRTAB = 49,
};

enum
{
    SYMTAB_NDX_UNDEF = 0,
    SYMTAB_NDX_TEXT,
    SYMTAB_NDX_DATA,
    SYMTAB_NDX_BSS,
    SYMTAB_NDX_MESSAGE_LEN,
    SYMTAB_NDX_MESSAGE_END,
    SYMTAB_NDX_MESSAGE_START,
    SYMTAB_NDX_CUSTOM_ENTRY,
};

enum
{
    SECTION_NDX_UNDEF = 0,
    SECTION_NDX_TEXT,
    SECTION_NDX_RELA_TEXT,
    SECTION_NDX_DATA,
    SECTION_NDX_BSS,
    SECTION_NDX_SYMTAB,
    SECTION_NDX_STRTAB,
    SECTION_NDX_SHSTRTAB,
};


extern int yylex();
extern FILE* yyin;
extern void yyrestart(FILE*);

std::vector<Sekcija*> sveSekcije;
std::vector<Simbol*> sviSimboli;

int section_size_shstrtab;
int section_size_strtab;

Elf64_Ehdr elfHeader;
std::vector<Elf64_Sym> symtab;
std::vector<uint8_t> strtab;
std::vector<uint8_t> shstrtab;
std::vector<Elf64_Shdr> sectionHeaders;


void generisiHeader(){
    elfHeader.e_ident[EI_MAG0] = 0x7f;
    elfHeader.e_ident[EI_MAG1] = 'E';
    elfHeader.e_ident[EI_MAG2] = 'L';
    elfHeader.e_ident[EI_MAG3] = 'F';
    elfHeader.e_ident[EI_CLASS] = ELFCLASS64;
    elfHeader.e_ident[EI_DATA] = ELFDATA2LSB;
    elfHeader.e_ident[EI_VERSION] = EV_CURRENT;
    elfHeader.e_ident[EI_OSABI] = ELFOSABI_SYSV;
    elfHeader.e_ident[EI_ABIVERSION] = 0;

    elfHeader.e_type = ET_REL;
    elfHeader.e_machine = EM_X86_64;
    elfHeader.e_version = EV_CURRENT;
    elfHeader.e_entry = 0;
    elfHeader.e_phoff = 0;
    elfHeader.e_shoff = 0; //OFFSET(elfFile, sectionHeaderTable);
    elfHeader.e_flags = 0;
    elfHeader.e_ehsize = sizeof(Elf64_Ehdr);
    elfHeader.e_phentsize = 0;
    elfHeader.e_phnum = 0;
    elfHeader.e_shentsize = sizeof(Elf64_Shdr);
    //ovo je izmenjeno
    elfHeader.e_shnum = sveSekcije.size();
    elfHeader.e_shstrndx = sveSekcije.size()-1;
}



int generisi_elf() {
    printf("aaaa\n");

    sveSekcije = DataTable::getInstance().getOrderedGen();
    printf("%zu\n", sveSekcije.size());

    int size = 1;

    for(int i=1;i<sveSekcije.size();i++){
        Sekcija* sekcija = sveSekcije[i];
        size += sekcija->getName().size() + 2;  //.\0
    }

    char* buffer_shstrtab = (char*)malloc(size);
    if (!buffer_shstrtab) return 0;

    section_size_shstrtab=size;

    int offset = 0;
    buffer_shstrtab[offset++] = '\0';

    for(int i=1;i<sveSekcije.size();i++){
        Sekcija* sekcija = sveSekcije[i];
        buffer_shstrtab[offset++] = '.';  // dodaj tacku
        std::memcpy(buffer_shstrtab + offset, sekcija->getName().c_str(), sekcija->getName().size());
        offset += sekcija->getName().size();
        buffer_shstrtab[offset++] = '\0';
    }

    printf("BUFFER:\n");
    printf("BUFFER SIZE: %d\n", size);
    /*fwrite(buffer, 1, size, stdout);
    printf("\n");*/


    /* .shstrtab */
    shstrtab.assign(buffer_shstrtab, buffer_shstrtab + section_size_shstrtab);
    int i1 = 0;
    while (i1 < shstrtab.size()) {
        printf("[%d] %s\n", i1, (char*)&shstrtab[i1]);
        i1 += strlen((char*)&shstrtab[i1]) + 1;
    }

    sviSimboli = DataTable::getInstance().getOrderedSimboli();
    printf("%zu\n", sviSimboli.size());

    int size1 = 1;

    for(int i=1;i<sviSimboli.size();i++){
        Simbol* simbol = sviSimboli[i];
        if(!simbol->getSectionOwner() || simbol->getSectionOwner()->getName()!=simbol->getName()){
            size1 += simbol->getName().size() + 1;  //.\0
        }
    }

    char* buffer_strtab = (char*)malloc(size1);
    if (!buffer_strtab) return 0;

    section_size_strtab=size1;

    int offset1 = 0;
    buffer_strtab[offset1++] = '\0';

    for(int i=1;i<sviSimboli.size();i++){
        Simbol* simbol = sviSimboli[i];
        if(!simbol->getSectionOwner() || simbol->getSectionOwner()->getName()!=simbol->getName()){
            std::memcpy(buffer_strtab + offset1, simbol->getName().c_str(), simbol->getName().size());
            offset1 += simbol->getName().size();
            buffer_strtab[offset1++] = '\0';
        }
    
    }

    printf("BUFFER:\n");
    printf("BUFFER SIZE: %d\n", size1);
    /*fwrite(buffer, 1, size, stdout);
    printf("\n");*/


    /* .strtab */
    strtab.assign(buffer_strtab, buffer_strtab + section_size_strtab);
    i1 = 0;
    while (i1 < strtab.size()) {
        printf("[%d] %s\n", i1, (char*)&strtab[i1]);
        i1 += strlen((char*)&strtab[i1]) + 1;
    }


    generisiHeader();

    for(int i=0;i<sviSimboli.size();i++){
        Simbol* s = sviSimboli[i];

        Elf64_Sym sym = {};

        
        sym.st_value = s->getValue();
        sym.st_size = s->getSize();

        if(s->getSectionOwner() && s->getSectionOwner()->getName()==s->getName()){
            sym.st_name = getOffset(s->getName().c_str(), buffer_shstrtab, size);
            sym.st_info = ELF64_ST_INFO(
            STB_LOCAL,
            STT_SECTION
        );
        }else if(s->getSectionOwner()){
            sym.st_name = getOffset(s->getName().c_str(), buffer_strtab, size1);
            sym.st_info = ELF64_ST_INFO(
                s->isGlobal() ? STB_GLOBAL : STB_LOCAL,
                STT_NOTYPE
            );
        }

        

        sym.st_other = 0;

        sym.st_shndx = 0;
        if(s->getSectionOwner()){
            sym.st_shndx = s->getSectionOwner()->getNdx();
        }

        symtab.push_back(sym);
        
    }


    FILE* f = fopen("test.o", "wb");

    fwrite(&elfHeader, sizeof(Elf64_Ehdr), 1, f);

    fwrite(shstrtab.data(), 1, shstrtab.size(), f);

    fwrite(strtab.data(), 1, strtab.size(), f);

    fwrite(symtab.data(),
       sizeof(Elf64_Sym),
       symtab.size(),
       f);

    fwrite(sectionHeaders.data(),
        sizeof(Elf64_Shdr),
        sectionHeaders.size(),
        f);

    fclose(f);


    

    struct ElfFile
    {
        Elf64_Ehdr elfHeader;
        uint8_t text[SECTION_SIZE_TEXT];
        uint8_t data[SECTION_SIZE_DATA];
        uint8_t bss[SECTION_SIZE_BSS];
        Elf64_Sym symtab[8];
        uint8_t strtab[SECTION_SIZE_STRTAB];
        Elf64_Rela relaText[1];
        uint8_t shstrtab[SECTION_SIZE_SHSTRTAB];
        Elf64_Shdr sectionHeaderTable[8]; //koliko sekcija ima
    };

    struct ElfFile elfFile = {};

    /* ELF header */
    elfFile.elfHeader.e_ident[EI_MAG0] = 0x7f;
    elfFile.elfHeader.e_ident[EI_MAG1] = 'E';
    elfFile.elfHeader.e_ident[EI_MAG2] = 'L';
    elfFile.elfHeader.e_ident[EI_MAG3] = 'F';
    elfFile.elfHeader.e_ident[EI_CLASS] = ELFCLASS64;
    elfFile.elfHeader.e_ident[EI_DATA] = ELFDATA2LSB;
    elfFile.elfHeader.e_ident[EI_VERSION] = EV_CURRENT;
    elfFile.elfHeader.e_ident[EI_OSABI] = ELFOSABI_SYSV;
    elfFile.elfHeader.e_ident[EI_ABIVERSION] = 0;

    elfFile.elfHeader.e_type = ET_REL;
    elfFile.elfHeader.e_machine = EM_X86_64;
    elfFile.elfHeader.e_version = EV_CURRENT;
    elfFile.elfHeader.e_entry = 0;
    elfFile.elfHeader.e_phoff = 0;
    elfFile.elfHeader.e_shoff = OFFSET(elfFile, elfFile.sectionHeaderTable);
    elfFile.elfHeader.e_flags = 0;
    elfFile.elfHeader.e_ehsize = sizeof(Elf64_Ehdr);
    elfFile.elfHeader.e_phentsize = 0;
    elfFile.elfHeader.e_phnum = 0;
    elfFile.elfHeader.e_shentsize = sizeof(Elf64_Shdr);
    //ovo je izmenjeno
    elfFile.elfHeader.e_shnum = sveSekcije.size();
    elfFile.elfHeader.e_shstrndx = sveSekcije.size()-1;

    //ovo je header tu je trebalo

    /* .text */
    {
        uint8_t textBytes[SECTION_SIZE_TEXT] = {
            0x48, 0xc7, 0xc0, 0x01, 0x00, 0x00, 0x00,
            0x48, 0xc7, 0xc7, 0x01, 0x00, 0x00, 0x00,
            0x48, 0xc7, 0xc6, 0x00, 0x00, 0x00, 0x00,
            0x48, 0xc7, 0xc2, 0x13, 0x00, 0x00, 0x00,
            0x0f, 0x05,
            0x48, 0xc7, 0xc0, 0x3c, 0x00, 0x00, 0x00,
            0x48, 0xc7, 0xc7, 0x0d, 0x00, 0x00, 0x00,
            0x0f, 0x05
        };
        memcpy(elfFile.text, textBytes, SECTION_SIZE_TEXT);
    }

    /* .data */
    memcpy(elfFile.data, "Hello World!\n", SECTION_SIZE_DATA);

    /* .strtab */
    memcpy(elfFile.strtab, STRTAB, SECTION_SIZE_STRTAB);

    /* .shstrtab */
    memcpy(elfFile.shstrtab, SHSTRTAB, SECTION_SIZE_SHSTRTAB);

    /* .symtab */
    elfFile.symtab[SYMTAB_NDX_UNDEF] = {};
    elfFile.symtab[SYMTAB_NDX_UNDEF].st_shndx = SHN_UNDEF;

    elfFile.symtab[SYMTAB_NDX_TEXT] = {};
    elfFile.symtab[SYMTAB_NDX_TEXT].st_info = ELF64_ST_INFO(STB_LOCAL, STT_SECTION);
    elfFile.symtab[SYMTAB_NDX_TEXT].st_shndx = SECTION_NDX_TEXT;

    elfFile.symtab[SYMTAB_NDX_DATA] = {};
    elfFile.symtab[SYMTAB_NDX_DATA].st_info = ELF64_ST_INFO(STB_LOCAL, STT_SECTION);
    elfFile.symtab[SYMTAB_NDX_DATA].st_shndx = SECTION_NDX_DATA;

    elfFile.symtab[SYMTAB_NDX_BSS] = {};
    elfFile.symtab[SYMTAB_NDX_BSS].st_info = ELF64_ST_INFO(STB_LOCAL, STT_SECTION);
    elfFile.symtab[SYMTAB_NDX_BSS].st_shndx = SECTION_NDX_BSS;

    elfFile.symtab[SYMTAB_NDX_MESSAGE_LEN].st_name =
        getOffset("message_len", STRTAB, SECTION_SIZE_STRTAB);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_LEN].st_info =
        ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_LEN].st_shndx = SHN_ABS;
    elfFile.symtab[SYMTAB_NDX_MESSAGE_LEN].st_value = 0x0e;

    elfFile.symtab[SYMTAB_NDX_MESSAGE_END].st_name =
        getOffset("message_end", STRTAB, SECTION_SIZE_STRTAB);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_END].st_info =
        ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_END].st_shndx = SECTION_NDX_DATA;
    elfFile.symtab[SYMTAB_NDX_MESSAGE_END].st_value = 0x0e;

    elfFile.symtab[SYMTAB_NDX_MESSAGE_START].st_name =
        getOffset("message_start", STRTAB, SECTION_SIZE_STRTAB);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_START].st_info =
        ELF64_ST_INFO(STB_LOCAL, STT_NOTYPE);
    elfFile.symtab[SYMTAB_NDX_MESSAGE_START].st_shndx = SECTION_NDX_DATA;
    elfFile.symtab[SYMTAB_NDX_MESSAGE_START].st_value = 0x00;

    elfFile.symtab[SYMTAB_NDX_CUSTOM_ENTRY].st_name =
        getOffset("custom_entry", STRTAB, SECTION_SIZE_STRTAB);
    elfFile.symtab[SYMTAB_NDX_CUSTOM_ENTRY].st_info =
        ELF64_ST_INFO(STB_GLOBAL, STT_NOTYPE);
    elfFile.symtab[SYMTAB_NDX_CUSTOM_ENTRY].st_shndx = SECTION_NDX_TEXT;

    /* .rela.text */
    elfFile.relaText[0].r_offset = 0x11;
    elfFile.relaText[0].r_info = ELF64_R_INFO(SYMTAB_NDX_DATA, R_X86_64_32S);
    elfFile.relaText[0].r_addend = 0x00;

    /* section headers */
    elfFile.sectionHeaderTable[SECTION_NDX_UNDEF] = {};

    elfFile.sectionHeaderTable[SECTION_NDX_TEXT].sh_name =
        getOffset(".text", SHSTRTAB, SECTION_SIZE_SHSTRTAB);
    elfFile.sectionHeaderTable[SECTION_NDX_TEXT].sh_type = SHT_PROGBITS;
    elfFile.sectionHeaderTable[SECTION_NDX_TEXT].sh_flags = SHF_EXECINSTR | SHF_ALLOC;
    elfFile.sectionHeaderTable[SECTION_NDX_TEXT].sh_offset = OFFSET(elfFile, elfFile.text);
    elfFile.sectionHeaderTable[SECTION_NDX_TEXT].sh_size = SECTION_SIZE_TEXT;

    elfFile.sectionHeaderTable[SECTION_NDX_DATA].sh_name =
        getOffset(".data", SHSTRTAB, SECTION_SIZE_SHSTRTAB);
    elfFile.sectionHeaderTable[SECTION_NDX_DATA].sh_type = SHT_PROGBITS;
    elfFile.sectionHeaderTable[SECTION_NDX_DATA].sh_flags = SHF_WRITE | SHF_ALLOC;
    elfFile.sectionHeaderTable[SECTION_NDX_DATA].sh_offset = OFFSET(elfFile, elfFile.data);
    elfFile.sectionHeaderTable[SECTION_NDX_DATA].sh_size = SECTION_SIZE_DATA;

    elfFile.sectionHeaderTable[SECTION_NDX_BSS].sh_name =
        getOffset(".bss", SHSTRTAB, SECTION_SIZE_SHSTRTAB);
    elfFile.sectionHeaderTable[SECTION_NDX_BSS].sh_type = SHT_NOBITS;
    elfFile.sectionHeaderTable[SECTION_NDX_BSS].sh_flags = SHF_WRITE | SHF_ALLOC;

    FILE *fileHandle = fopen("generated.o", "wb");
    if (!fileHandle) {
        perror("fopen");
        return 1;
    }

    fwrite(&elfFile, sizeof(struct ElfFile), 1, fileHandle);
    fclose(fileHandle);

    return 0;
}










int main() {

    

    const char* inputFile = "tests/test.s";

    printf("ULAZIM U PARSER1\n");
    yyin = fopen(inputFile, "r");

    yyparse();
    fclose(yyin);
    printf("IZLAZIM IZ PARSER1\n");

    DataTable::getInstance().setPrviProlaz();

    printf("ULAZIM U PARSER2\n");
    yyin = fopen(inputFile, "r");
    yyrestart(yyin);
    yyparse();
    fclose(yyin);
    printf("IZLAZIM IZ PARSER2\n");

    generisi_elf();
    /*FILE *fileHandle = fopen("generated.o", "wb");
    char str[] = "hello world\n";
    fwrite(str, 1, strlen(str), fileHandle);*/
    return 0;
}