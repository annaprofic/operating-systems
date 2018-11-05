#include <unistd.h>  
#include <stdlib.h>
#include <stdio.h>
#include "sem.h"
#include "shmem.h"
#define MAX 10

int i = 0; 

typedef struct cykliczny {
     int size;
     char bufor[MAX];
} bufor;

int main (int argc, char *argv[]) {

    int semid = 0; //semafory
    int shmid = 0; //pamiec

    if(argc != 1) {
        perror("Prosze wpisac jeden argument.\n");
        exit(1);
    }

    // pamiec
    shmid = shmCreate(1, MAX);
    // semafory

    semid = semDecl(1, 2); // id, zestaw semaforow

    semInit(semid, 0, MAX); //poczatkowy semafow wartoscia MAX
    semInit(semid, 1, 0); // otrzymuje 0

    switch(fork()) {

        case -1:
            printf("Nie mozna utworzyc procesu potomnego!\n");
            exit(1);
            break;
        case 0:
            if (execl("./producent.x", "./producent.x", NULL) == -1) { 
                perror("Blad przy wykonaniu funkcji exec!\n"); 
                exit(2);
            }
            break;
        default:
            break;
    }
    
    sleep(1);

    switch(fork()) {

        case -1:
            printf("Nie mozna utworzyc procesu potomnego!\n");
            exit(1);
            break;
        case 0:
            if (execl("./konsument.x", "./konsument.x", NULL) == -1) { 
                perror("Blad przy wykonaniu funkcji exec!\n"); 
                exit(2);
            }
            break;
        default:
            break;
    }
   
    wait(NULL); 
    wait(NULL); 

    semRm(semid, 2);
    shmRm(shmid);
   
    execl ("/bin/sh", "sh", "-c", "diff -s magazyn.txt schowek.txt", NULL);

    return 0;
}