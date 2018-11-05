#include"sem.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <string.h>

int main (int argc, char const *argv[0]) { 

    if (argc != 3 ) { // sprawdzanie poprawnej ilosci argumentow 
    printf("Niepoprawna ilosc argumentow.\n");
    printf("Prosze wpisac komende:\n./powielacz.x ./prog.x 'liczbe procesow'.\n");
    return 1;
    }    
    int i = 0; 
    int child = 0; 
    int iloscproc = atoi(argv[2]);

    char * argv1[argc]; // tablica do prechowywania argomentow

    for (i = 0; i < argc; i ++ ) { // alokowanie pamieci dla tablicy argv1 
		argv1[i] = malloc(strlen(argv[i])+1);
	}
    
	for (i = 0; i < argc-1; i ++ ) { // kopiowanie argumentow programu do stworzonej tablicy 
		strcpy(argv1[i], argv[i+1]);
	}
	argv1[i] = NULL;
    
    printf("\n");
    int semid = semDecl(1); // tworzenie
    semInit(semid, 1); //inicjalizacja
    printf("\n");

    char numerprocesu[10];

    for (i = 0; i < iloscproc; i++) { 
        switch (fork())  { 
            case -1: 
                perror("Nowego procesu potomnego nie da sie utworzyc.\n"); 
                exit (1); 
            case 0:
                sprintf(numerprocesu, "%d", i + 1);
                if (execl(argv1[0], argv1[0], numerprocesu, NULL) == -1) { //przekazuje argumenty do programy 'prog'
                    perror ("Wystapil blad przy wywolaniu funkcji exec\n"); 
                    exit(1);
                }
                break; 
            default: 
                child ++;       
                break;
        }
	}
    for (i = 0; i < iloscproc; i++) { // czeka na proces potomny
    wait(NULL);
    }

    semRm(semid); 

    for (i = 0; i < argc-1; i ++ ) { // zwalnanie pamieci tablicy 
		free(argv1[i]);
	}

    return 0; 
}