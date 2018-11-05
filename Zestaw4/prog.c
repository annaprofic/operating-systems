#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main (int argc, char const *argv[0] ) {

    if (argc != 2 ) { // sprawdzanie poprawnej ilosci argumentow 
    printf("Niepoprawnie przkazana przez exec ilosc argumentow.\n");
    return 1;
    }    
    
    int proces = atoi(argv[1]);
    int semid = semDecl(1);

    for (int i = 0; i < 2; i ++ ) {

        semInfo(semid); // info 

        semP(semid); // opuszczanie semafora

        printf("\t");
        printf ("proces %d __OPUSZCZENIE__\n", proces);
        
        usleep(rand()%999999);

        printf("\t");
        printf("proces %d __SEKCJA KRYTYCZNA__\n", proces); //sekcja krytyczna

        semInfo(semid);

        usleep(rand()%999999);

        printf("\t");
        printf ("proces %d __PODNIESIENIE__\n", proces);

        semV(semid); // podniesienie semafora
        semInfo(semid); // info 

    }
    
    return 0;
}
    
     