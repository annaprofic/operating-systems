#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

int main (int argc, char const *argv[0] ) {
    
    if (argc != 2 ) { // sprawdzanie poprawnej ilosci argumentow 
    printf("Niepoprawna ilosc argumentow.\n");
    printf("Prosze wpisac komende:\n./semuse.x 'rodzaj akcji: (i, r, p, v, z, lub q)'.\n");
    return 1;
    }
    int sem = semDecl(1);
    
    switch (*argv[1]) {

        case 'i': 
            semInit(sem, 1); 
            semInfo(sem);
            break; 

        case 'r': 
            semRm(sem);
            break; 

        case 'p': 
            semP(sem);
            semInfo(sem);
            break; 

        case 'v': 
            semV(sem);
            semInfo(sem);
            break; 

        case 'z': 
            semZ(sem);
            semInfo(sem);
            break; 

        case 'q': 
            semInfo(sem);
            break;

        default:  
            perror("Prosze wpisac poprawnie rodzaj akcji. \nKomenda:\n./semuse.x 'rodzaj akcji: (i, r, p, v, z, lub q)'.\n");
            exit(1);
    }
return 0; 
}
