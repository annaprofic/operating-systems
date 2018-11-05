#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifdef _SEM_SEMUN_UNDEFINED
     union semun {
       int val;               // wartosc dla SETVAL 
       struct semid_ds *buf;  // bufor dla IPC_STAT, IPC_SET 
       unsigned short *array; // tablica dla GETALL, SETALL 
       struct seminfo *__buf; // bufor dla IPC_INFO (specyfika Linuksa) 
}; 
#endif

int semDecl(int id) {
    key_t key;
    int semid = 0;
    printf("Uzyskanie dostepu do semaforu / tworzenie semaforu ... \n");

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego dla zbioru semaforow
        perror("Wystapil blad przy tworzniu klucza do semaforow!\n");
        exit(1);
    }

    if ((semid = semget(key, id, IPC_CREAT | 0666)) == -1 ){ // tworzeniu lub uzyskiwanie dostepu do zbioru semaforow
        perror("Wystapil blad przy tworzeniu zbioru semaforow!\n");
        exit(1);
    }
    return semid;
}

void semInit(int semid, int val) { // inicjalizacja semafora wartoscia val
    int inicjalizacja = 0;
    printf("Inicjalizuje semafor %d...\n", val);

    if ((inicjalizacja = semctl(semid, 0, SETVAL, val)) == -1){
        perror("Wystapil blad inicjalizacji semafora!\n");
        exit(1);
    }
}

void semRm(int semid) {
    int usuwanie = 0;
    printf("Usuwanie semaforu...\n");
    
    if((usuwanie = semctl(semid, 0, IPC_RMID)) == -1) {
        perror("Wystapil blad przy usuwaniu semafora!\n");
    }
}

void semP(int semid) { // opuszczanie semafora: zmniejsza wartosc o 1 lub czeka 
    printf("Opuszczanie semaforu, zmnejszanie wartosci...\n");   
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = -1; // < 0 operacja P na semaforze
    buf.sem_flg = 0; // znacznik = operacja blokujaca
    if (semop(semid, &buf, 1) == -1) { 
        perror("Wystapil blad przy opuszczenie semafora!\n"); 
        exit(1);
    }

}

void semV(int semid) { // podnosi semafor: zwieksza wartosc semafora o 1 lub wznawia czekajacy proces
    printf("Podniesienie semaforu, zwiekszanie wartosci...\n");   
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 1; // > 0 operacja V na semaforze
    buf.sem_flg = 0; //operacja blokujaca
    if (semop(semid, &buf, 1) == -1) { 
        perror("Wystapil blad przy podnoszeniu semafora!\n"); 
        exit(1);
    }

}

void semZ(int semid) { // czeka na wyzerowanie semafora
    printf("Czekam na wyzerowanie semaforu...\n");       
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 0; // = 0 operacja Z na semaforze
    buf.sem_flg = 0; //operacja blokujaca
    if (semop(semid, &buf, 1) == -1) { 
        perror("Wystapil blad funkcji czekajacej na wyzerowanie semafora!\n"); 
        exit(1);
    }
}

void semInfo(int semid) {
    int wartosc = 0; 
    int czekaniena_podniesienie = 1;
    int czekaniena_opuszczenie = 1;

    if ((wartosc = semctl(semid, 0, GETVAL)) == -1) { 
        perror ("Wystapil blad przy wypisywaniu wartosci semafora");
        exit (1);
    }
    printf ("Wartosc semafora: %d\n", wartosc);

    if ((czekaniena_podniesienie = semctl(semid, 0, GETNCNT)) == -1) {
        perror ("Wystapil blad przy wypisywaniu czekujacych procesow");
        exit (1);
    }
    printf ("procesy czekajace na podnesienie: %d, ", czekaniena_podniesienie);

    if ((czekaniena_opuszczenie = semctl(semid, 0, GETZCNT)) == -1) { 
        perror ("Wystapil blad przy wypisywaniu czekujacych procesow");
        exit(1); 
    }
    printf (" procesy czekajace na opuszczenie: %d\n", czekaniena_opuszczenie);
}