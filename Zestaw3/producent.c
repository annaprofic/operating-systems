#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
ssize_t file_write;
char buffor[128];
int potokdes1;
FILE *potok1;

void producent (const char *potokfifo) {

    potok1 = fopen("magazyn.txt", "r"); // otwieramy olik w trybie read 
    if ( potok1 == NULL ) {
          perror("Plik 'magazyn.txt nie udalo sie otworzyc'.");
          exit(1);
    }

    potokdes1 = open(potokfifo, O_WRONLY); // tworzymy deskryptor pliku
    if ( potokdes1 == -1 ) {
          perror("Plik potoku nazwanego nie udalo sie otworzyc'.");
          exit(1);
    }

    while (!(feof(potok1))) { 
          fgets(buffor, 128, potok1);
          usleep(rand() % 2000000);
          file_write = write(potokdes1, &buffor, 128);
          printf("Producent --> %s\n", buffor);
          if (file_write == -1 ) {
                perror("Blad przesylania danych do Konsumenta.\n");
                exit(1) ;
          }
    }

    if (fclose(potok1) != 0 ) {
          perror ("Plik 'magazyn.txt' nie udalo sie zamknac");
          exit(1);
    }

    if (close(potokdes1) == -1) {
          perror ("Blad przy zamykaniu pliku potoku nazwanego");
    }
}

int main (int argc, char const *argv[]) {

    producent(argv[1]);
    return 0;
}
