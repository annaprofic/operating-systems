#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>  

int shmCreate(int id, int size) { // funkcja tworzaca albo uzyskujaca dostep do pamieci dzielonej
    key_t key;
    int shmid; 
    printf("Tworze pamiec dzielona...");

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego 
        perror("Wystapil blad przy tworzniu klucza!\n");
        exit(EXIT_FAILURE);
    }

    if ((shmid = shmget(key, size, IPC_CREAT | IPC_EXCL  | 0666)) == -1) { 
        perror("Wystapil blad przy tworzeniu pamieci dzielonej!\n");
        exit(EXIT_FAILURE);
    }
    printf("Pamiec stworzona!\n");
    return  shmid;
}

int shmOpen(int id) { // uzyskuje dostep do pamieci, umozliwia korzytanie z pamieci
    key_t key;
    int shmid;

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego 
        perror("Wystapil blad przy tworzniu klucza!\n");
        exit(EXIT_FAILURE);
    }

    if ((shmid = shmget(key, 0, 0666)) == -1) { 
        perror("Wystapil blad dostepu do pamieci dzielonej!\n");
        exit(EXIT_FAILURE);
    }
    return  shmid;
}

void shmRm(int shmid) { //Usuwa dany segment pamieci dzielonej shmid
    
    printf("Usuwam podany segment pamieci dzielonej...\n");
    if (shmctl(shmid, IPC_RMID , (struct shmid_ds *)0) == -1 ) { 
        perror ("Wystapil blad przy usuwaniu segmetu pamieci!\n");
        exit(EXIT_FAILURE);
    }
    printf("Dany segment pamieci zostal usuniety!\n");
}

void* shmAt(int shmid) { //Dowiazuje segment pamieci dzielonej shmid. Zwraca adres odwzorowania

    void * adres = shmat(shmid, NULL, 0);
    return adres; 
}

void shmDt(void *adres) { //Usuwa dowiazanie do segmentu pamieci dzielonej dowiazanej pod adres

    if (shmdt( adres ) == -1) {
        perror ("Wystapil blad przy usuwaniu segmentu pamieci!\n");
        exit(EXIT_FAILURE);
    } 
}

void przerwanie(int sygnal) {  // funkcja ktora przerywa petle, usuwajac stworzona paiec dzielona, wywoluje sie 2 razy 

    printf("\nPrzerwanie programu.\n");
    int shmid; 
    shmid=  shmOpen(1); 
    shmRm(shmid);

}

