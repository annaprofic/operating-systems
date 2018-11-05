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

union semun arg;
struct sembuf buf;

int semDecl(int id, int semnum) {
    key_t key;
    int semid;
    printf("Uzyskanie dostepu do semaforu / tworzenie semaforu ... \n");

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego dla zbioru semaforow
        perror("Wystapil blad przy tworzniu klucza do semaforow!\n");
        exit(1);
    }

    if ((semid = semget(key, semnum, IPC_CREAT | 0666)) == -1 ){ // tworzeniu lub uzyskiwanie dostepu do zbioru semaforow
        perror("Wystapil blad przy tworzeniu zbioru semaforow!\n");
        exit(1);
    }
    return semid;
}

void semInit(int semid, int semnum, int val) { // inicjalizacja semafora wartoscia val
   
    arg.val = val;
    printf("Inicjalizuje semafor %d...\n", val);

    if ((semctl(semid, semnum, SETVAL, arg)) == -1){
        perror("Wystapil blad inicjalizacji semafora!\n");
        exit(1);
    }
}

void semRm(int semid, int semnum) {

    printf("Usuwanie semaforu...\n");
    
    if ((semctl(semid, semnum, IPC_RMID, arg)) == -1) {
        perror("Wystapil blad przy usuwaniu semafora!\n");
        exit(1);
    }
}

void semP(int semid, int semnum) { // opuszczanie semafora: zmniejsza wartosc o 1 lub czeka 
    printf("Opuszczanie semaforu, zmnejszanie wartosci...\n");   
    buf.sem_num = semnum;
    buf.sem_op = -1; // < 0 operacja P na semaforze
    buf.sem_flg = 0; // znacznik = operacja blokujaca
    if ((semop(semid, &buf, 1)) == -1) { 
        perror("Wystapil blad przy opuszczenie semafora!\n"); 
        exit(1);
    }

}

void semV(int semid, int semnum) { // podnosi semafor: zwieksza wartosc semafora o 1 lub wznawia czekajacy proces
    printf("Podniesienie semaforu, zwiekszanie wartosci...\n");   
    buf.sem_num = semnum;
    buf.sem_op = 1; // > 0 operacja V na semaforze
    buf.sem_flg = 0; //operacja blokujaca
    if ((semop(semid, &buf, 1)) == -1) { 
        perror("Wystapil blad przy podnoszeniu semafora!\n"); 
        exit(1);
    }

}

void semZ(int semid) { // czeka na wyzerowanie semafora
    printf("Czekam na wyzerowanie semaforu...\n");       
    buf.sem_num = 0;
    buf.sem_op = 0; // = 0 operacja Z na semaforze
    buf.sem_flg = 0; //operacja blokujaca
    if ((semop(semid, &buf, 1)) == -1) { 
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