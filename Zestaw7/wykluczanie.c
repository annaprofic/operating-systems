#define _REENTRANT
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define kursyw "\x1B[3m"
#define green "\x1B[32m"
#define red "\x1B[31m"
#define N 4

// muteks negocjuje dostep miedzy watkami ( tak zwana blokada )
pthread_mutex_t muteks = PTHREAD_MUTEX_INITIALIZER;  // muteks zdefiniowany jako otwarty (wartosc = 0)
volatile unsigned int counter = 0;

void * watek(void *arg) {
    
    int iloscW=(long)arg; // ilosc watkow
    int j = 0, i = 0;  

    for ( i = 0; i < 3; i ++) {

        printf(green"\033[7m\033[%d;40HSEKCJA PRYWATNA.\033[0m  counter  %u \033[0m\n", iloscW+4, counter);

        pthread_mutex_lock(&muteks); // zajecie sekcji krytycznej
        // przy zajeciu sekcji krytycznej mamy dostep do zmiennej count
        j = counter;
        j += 1;
        
        
        printf("\033[%d;40H                                             \033[0m\n", iloscW+4); 
        printf(red"\033[7m\033[%d;80HSEKCJA KRYTYCZNA.\033[0m  counter  %u \033[0m\n", iloscW+4, counter );   
        counter = j;
        sleep(1);

        pthread_mutex_unlock(&muteks); // opuszczanie sekcji krytycznej
        printf("\033[%d;80H                                              \033[0m\n", iloscW+4); 
    }
    
    return 0;
}

int main(int argc, char const * argv[]) {

    long c ; 
    system("clear"); // oczyszczenie ekranu  na poczatku uruchamiania
    pthread_t pthreadID[N]; // niepowtarzalny identyfikator watku 

    for (c = 0; c < N; c ++) {

        if ( pthread_create( &pthreadID[c], NULL, watek, (void*)(c + 1 )) ) { // tworzenie - identyfikator, domyslne atrybuty 
            perror("error pthread_create\n");
            exit(EXIT_FAILURE);
        }
    }

    for (c = 0; c < N; c ++) {

        if ( pthread_join ( pthreadID[c], NULL ) ) { // czekanie 
            perror("error pthread_join");
            exit(EXIT_FAILURE);
        }
    } 

    
    pthread_mutex_destroy(&muteks);

    printf(kursyw"\n\n\nWartosc koncowa: %d\n", counter);
    pthread_exit(NULL); // zakonczenie dzialania watkow 
    
    return 0; 
}