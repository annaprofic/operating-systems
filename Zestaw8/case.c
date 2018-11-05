#include <time.h>        
#include <sys/sem.h>   
#include <stdlib.h>      
#include <unistd.h> 
#include <stdio.h>     
#include "shmem.h"

int main (int argc, char * argv[]) {

    if (argc != 2) { // sprawdzamy czy ilosc atgomentow jest poprawna
        perror("Nieprawidlowa ilosc argumentow przeekazana przez funkcje exec!\n");
        exit(EXIT_FAILURE);
    }

    zmienne * zm;  // zmienna wskazujaca na strukture 

    int shmid = 0;
    shmid = shmOpen(1); // uzyskanie dostepu do pamieci sweorzonej w main.c

    zm = (zmienne*)shmAt(shmid); // dowiazujeny segment pamieci 
    
    int i = 0, j = 0; 
    i = atoi(argv[1]); // char to int 
    j = 1 - i; // 0 albo 1 w zaleznosci od ustawionego i

    printf ("\n\n");

    do { 
        
        zm->flaga[i] = TRUE; // oznacza ze dany proces chce wejsc do sekcji krytycznej 
        zm->kolej = j; // oznacza proces, ktory czeka 

        // za pierwsza iteracja proces nr pod numerem i = 0 chce wejsc do sekcji a proces 1-i czyli j = 1 czeka 
        // za druga proces i = 1 chce wejsc, a j = 0 czeka
        printf("\t\t\tProces %d chce wejsc do sekcji krytycznej\n", i);
        printf("\t\t\tProces %d w kolei...\n", i);
        
        while (zm->flaga[j] && zm->kolej == j) { // jezeli proces j chce wejsc do sekcji tp czeka
            sleep(2); 
        } 
        printf(red"\t\t\tProces %d jest w SEKCJI KRYTYCZNEJ\033[0m\n", i); 
        printf("\t\t\tProces zmienia swoj status...\n");
        
        zm->flaga[i] = FALSE; // proces zmienia swoj status

        printf(green"Proces %d w sekcji prywatnej\033[0m\n", i);
    
    } while(1); 

return 0;

}


