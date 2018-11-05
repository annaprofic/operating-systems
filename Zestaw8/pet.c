#include <time.h>        
#include <sys/sem.h>   
#include <stdlib.h>      
#include <unistd.h> 
#include <stdio.h>     
#include "shmem.h"


int main (int argc, char const * argv[]) {

    if (argc != 1) { // sprawdzamy czy ilosc atgomentow jest poprawna
        perror("Nieprawidlowa ilosc argumentow!\n Prosze wpisac ./pat.x\n");
        exit(EXIT_FAILURE);
    }

    if (signal(2, przerwanie) == SIG_ERR) {     // przechwycenie obslugi sygnalu sigint, wykonanie wlasnej funkcji 
            perror(red"error SIGNAL\n"reset);   // wlasna funkja 'przerwanie' znajduje sie w bibliotece dynamicznej 'shmem.h'
            exit(EXIT_FAILURE);
    }

    zmienne * zm; // zmienna wskazujaca na strukture 
    int number_of_process = 0, shmid = 0, size = 0;  // numer procesu, id pamieci dzielonej, rozmiar danych 
    char process[2]; // tablica dla przekazywania numeru procesu jako zmiennej 
    size = sizeof(zmienne); // sprawdzamy rozmiar danych 
    
    system("clear"); // oczyszczanie ekrany poprez funkcje systemowa

    printf("\n\033[7mZeby zatrzymac program i usunac stworzony fragment pamieci prosze wcisnac CTRL+C\n"reset);

    shmid = shmCreate(1, size); // tworzenie pamieci dzielonej
    
    zm = (zmienne*)shmAt(shmid); // dowiazujeny segment pamieci 

    zm->kolej = 0; 
    zm->flaga[0] = 0; 
    zm->flaga[1] = 0; 

    for (number_of_process = 0; number_of_process < 2; number_of_process ++ ) { // petla uruchamia sie dla 2 procesow 

        switch(fork()) {

            case -1:
                printf(red"Nie mozna utworzyc procesu potomnego!\n"reset);
                exit(EXIT_FAILURE);
                break;

            case 0:
                // Przekazujemy do case.c numer procesu jako argument
                // A char in C is already a number (the character's ASCII code), no conversion required.
                process[number_of_process] = number_of_process + '0';  // The '0' is a character in the ASCII table.
                printf("\nNUM OF PROCESS %d in ASCII Hex Symbol %d\n", process[number_of_process],number_of_process );

                if (execl("./case.x", "./case.x", &process[number_of_process] , NULL) == -1) {
                    perror (red"error exec\n"reset); 
                    exit(EXIT_FAILURE);
                } 

                break;

            default: break;
        }
    }


    shmDt(zm); // usuwanie dowiazania pamieci dzielonej 
    
    wait(NULL); // proces macierzysty czeka na proces potomny 1
    wait(NULL); // proces macierzysty czeka na proces potomny 2

    return 0; 
}
