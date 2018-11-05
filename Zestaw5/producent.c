#include <stdio.h>
#include <stdlib.h>      
#include <unistd.h>      
#include <time.h>       
#include "shmem.h"
#include "sem.h"

#define MAX 10
int i = 0;

typedef struct cykliczny {
    int size;           
    char dane[MAX];
} bufor; 

int main(int argc, char*argv[]) {

    srand(time(NULL));
    
    int semid = 0; 
    int shmid = 0; 
    char dane;
    bufor * buf;
    FILE* file1;
    shmid = shmOpen(1);
    semid = semDecl(1, 2); // ten sam id co i w glowny.c

    printf ("=============producent=============\n");

    //otwieranie pliku z ktorego pobieramy
    file1 = fopen("magazyn.txt", "r");
    if ( file1 == NULL ) {
        perror("Plik 'magazyn.txt' nie udalo sie otworzyc!\n");
        exit(1);
    }
    
     // dowiazanie do bufora

    if ((buf = (bufor *)shmAt(shmid))== NULL){
		perror("Blad: przylaczenie segmentu pamieci wspoldzielonej!\n");
		exit(1);
 	}

    for (i = 0; (dane = fgetc (file1)) != EOF; i++, buf->size ++ ) {

        // semafor ma poczatkowa wartosc MAX, zatem mozna wykonac MAX operacji zapisu, 
        // zapelnic calkowicie bufor, ktorego rozmiar jest rowny MAX
        // semafor osiagnie tym samym wartosc 0 i przy kolejnym obrocie petli nastapi zablokowanie procesu 
        // w operacji opuszczania tego semafora, az do momentu podniesienia go przez inny proces
        // proces konsumenta (odczytujący)

        semP (semid, 0); //opuszczanie 1 
        printf ("Przekazuje\n");
        usleep (rand() % 900);

        buf->dane[i % MAX] = dane;
        printf("Pozycja: %5d (magazyn) --> %5c\n", i, dane);
        // semafor nr 1 blokuje konsumenta przed dostępem do pustego bufora
        semV (semid, 1); // podnosze 2  
    }
    // zamykanie pliku 
    fclose(file1); 
    shmDt(buf);
 
    return 0;
}