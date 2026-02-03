#include <stdio.h>
#include <string.h>
#include "firstPass.h"


int locationCounter = 0;   // JEDINA prava definicija

int novaSekcija(){
    printf("Nova sekcija");
    locationCounter=0;

}

int visitNaredba(){
    printf("Usli smo u naredbu\n");
}