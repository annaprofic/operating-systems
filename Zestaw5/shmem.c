#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>  

int shmCreate(int id, int size) { // funkcja tworzaca albo uzyskujaca dostep do pamieci dzielonej
    key_t key;
    int shmid; 
    printf("Tworze pamiec dzielona...\n");

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego 
        perror("Wystapil blad przy tworzniu klucza!\n");
        exit(1);
    }

    if ((shmid = shmget(key, size, IPC_CREAT | IPC_EXCL  | 0666)) == -1) { 
        perror("Wystapil blad przy tworzeniu pamieci dzielonej!\n");
        exit(2);
    }
    return  shmid;
}

int shmOpen(int id) { // uzyskuje dostep do pamieci, umozliwia korzytanie z pamieci
    key_t key;
    int shmid;
    printf("Uzyskuje dostep do pamieci dzielonej...\n");

    if ((key = ftok(".", id)) == -1 ) { //tworzenie klucza jednoznacznego 
        perror("Wystapil blad przy tworzniu klucza!\n");
        exit(3);
    }

    if ((shmid = shmget(key, 0, 0666)) == -1) { 
        perror("Wystapil blad dostepu do pamieci dzielonej!\n");
        exit(4);
    }
    printf("Dostep zostal uzyskany!\n");
    return  shmid;
}

void shmRm(int shmid) { //Usuwa dany segment pamieci dzielonej shmid
    
    printf("Usuwam podany segment pamieci dzielonej...\n");
    if (shmctl(shmid, IPC_RMID , (struct shmid_ds *)0) == -1 ) { 
        perror ("Wystapil blad przy usuwaniu segmetu pamieci!\n");
        exit(5);
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
        exit(7);
    } 
}

int shmSize(int shmid) { // zwraca rozmiar pamieci dzielonej shmid 
    struct shmid_ds buf; // uzyskanie struktury odpowiadajacej segmentowi pamieci dzielonej 
  
     if(shmctl(shmid, IPC_STAT, &buf) == -1) {
          perror("Wystapil blad przy uzyskiwaniu rozmiaru pamieci!\n");
          exit(8);
     }
     return buf.shm_segsz; // Size of segment (bytes)
}


void shmInfo(int shmid) { // wypisuje informacje o pamieci dzielonej: prawa dostepu, rozmiar, pid tworcy, liczbe dowiazan 
    struct shmid_ds buf; // uzyskanie struktury odpowiadajacej segmentowi pamieci dzielonej 
     if(shmctl(shmid, IPC_STAT, &buf) == -1) {
          perror("Wystapil blad przy wypisywaniu unformacji!\n");
          exit(9);
     }
     printf ("Informacja o pamieci dzielonej:\n");
     printf ("Prawa dostepu: %d\nRozmiar: %zu\nPID tworcy: %d\nLiczba dowiazan: %d\n", buf.shm_perm.mode, buf.shm_segsz, buf.shm_cpid, buf.shm_nattch);
}
