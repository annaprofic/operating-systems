#include <stdio.h>
#include <stdlib.h>
#include "shmem.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main (int argc, char const *argv[0] ) {

    int sizeofseg = 0;
    int shmid = 0;
    int size = 128; 
    int i = 0;

    if (argc == 1) { 
        printf ("Uzycie programu:\nNalezy wpisac jednoliterowy argument, ktory wskazuje na odpowiednia akcje.\nc size - Tworzy segment pamieci o rozmiarze size bajtow\nd - Usuwa segment pamieci dzielonej\nr - Wypisuje zawartosc pamicci dzielonej na standardowe wyjscie\nw < input.txt - Kopiuje zawartosc standardowego wejscia do pamieci dzielonej\ni - Wypisuje informacje o pamieci dzielonej");
    }
    
    if (argc == 2) {

        switch (*argv[1]) {

        case 'c':  
            shmCreate(1, size);
            break; 
        case 'd': 
            shmid = shmOpen(1);
            shmRm(shmid);
            break; 
        case 'r': 
            shmid = shmOpen(1);
            printf ("Dane zostaly odczytane!\n");
            char *shmpointer1 = shmAt(shmid);
            printf("%s", shmpointer1);
            sizeofseg = shmSize(shmid);
            printf ("\nRozmiar segmentu dolaczonego: %d\n", sizeofseg);
            shmDt(shmpointer1);
            break; 
        case 'w': 
            shmid = shmOpen(1);
            char *shmpointer2 = shmAt(shmid);
            while (!(feof(stdin))) {
                fscanf(stdin, "%c", &shmpointer2[i] ); 
                printf("znak %c na pozycji %d\n", shmpointer2[i], i);
                i++; 
            } 
            break;
        case 'i': 
            shmid = shmOpen(1);
            shmInfo(shmid);
            break;
        default:  
            printf("Prosze wpisac komende:\n./shmuse.x 'rodzaj akcji: (c, d, r, w, i)'.\n");
            exit(1);
        }
    }
    
    if (argc == 3) {
        int size = 0;
        size = atoi(argv[2]);
        shmCreate(1, size);
    }
    
return 0; 
}
