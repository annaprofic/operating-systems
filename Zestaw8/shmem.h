// plik naglowkowy gdzie miesci sie interfejs modulu - deklaracja funkcji
#ifndef SHMEM_H
#define SHMEM_H
// flagi oznaczajace proces ktory ma wejsc do sekcji (kolej)
#define TRUE 1 // wartosc dla flagi true lub false
#define FALSE 0 

#define kursyw "\x1B[3m" // kolory 
#define green "\x1B[32m"
#define red "\x1B[31m"
#define reset "\033[0m"

typedef struct zmienne { // "bufor" zmiennych dla wejscia/wyjscia procesow do sekcji
    int kolej; 
    int flaga[2];
} zmienne;

int shmCreate(int id, int size);
int shmOpen(int id);
void shmRm(int shmid);
void* shmAt(int shmid);
void shmDt(void *adres);
void przerwanie(int sygnal);

#endif
