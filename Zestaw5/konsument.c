#include <time.h>        
#include <sys/sem.h>   
#include <stdlib.h>      
#include <unistd.h> 
#include <stdio.h>     
#include "shmem.h"
#include "sem.h"
#define MAX 10

int i = 0;

typedef struct cykliczny { 
   int size;          
   char dane[MAX]; 
} bufor; 

int main(int argc, char* argv[]) {

    srand(time(NULL));

    int semid = 0; 
    int shmid = 0; 
    int zapisane = 0;    
    char dane;
    bufor * buf;
    FILE* file2;
    shmid = shmOpen(1); 
    semid = semDecl(1, 2);

    printf ("=============konsument=============\n");

    // otwieranie pliku w trybie write - do zapisaneisu
    file2 = fopen("schowek.txt", "w"); 
    if ( file2 == NULL ) {
        perror("Plik 'schowek.txt' nie udalo sie otworzyc.");
        exit(1);
    }

    if ((buf = (bufor *)shmAt(shmid) )== NULL){
		perror("Blad: przylaczenie segmentu pamieci wspoldzielonej!\n");
		exit(1);
 	}
    
    // semafor nr 0 po odczytaniu pliku ma zapelniony bufor, ktorego rozmiar jest rowny MAX
    for ( i = 0, zapisane = 0; !(( semctl(semid, 0, GETVAL) == MAX) && (zapisane == buf->size)); i ++, zapisane ++) { 

        // po skonczeniu petli producenta semafor jest w stanie zablokowanym, poki inny proces ( w petli konsumenta) go nie odblokuje
        semP(semid, 1); //opuszczanie 2
        printf ("Pobieram\n"); 
        usleep(rand() % 900);
        dane = buf->dane[i % MAX];
        if (fputc(dane, file2) == EOF) { 
            perror("Blad zapisywania danych!\n"); 
            exit (1); 
        }
        printf("Pozycja: %5d --> (schowek): %5c\n", i, dane);
        semV(semid, 0); //podnosze 1
    }
    // zamykanie pliku 
    fclose(file2);  
    shmDt(buf);

    return 0;
}