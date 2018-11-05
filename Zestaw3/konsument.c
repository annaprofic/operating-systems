#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
ssize_t file_read;
char buffor[128];
int potokdes2;
FILE *potok2;

void konsument (const char *potokfifo) {

    potok2 = fopen("schowek.txt", "w");
    if (potok2 == NULL ) {
          perror("Plik 'schowek.txt nie udalo sie otworzyc'.");
          exit(1);
    }
    potokdes2 = open(potokfifo, O_RDONLY);
    if ( potokdes2 == -1 ) {
          perror("Plik potoku nazwanego nie udalo sie otworzyc'.");
          exit(1);
    }

    while ((file_read = read(potokdes2, &buffor, 128)) > 0 ) {
          usleep(rand() % 2000000);
          printf("  --> Konsument %s\n", buffor);
          fputs(buffor, potok2);
    }

    if (fclose(potok2) != 0 ) {
          perror ("Plik 'magazyn.txt' nie udalo sie zamknac");
          exit(1);
    }

    if (close(potokdes2) == -1) {
          perror ("Blad przy zamykaniu pliku potoku nazwanego.");
    }
}
int main(int argc, char const *argv[]) {
    konsument(argv[1]);
    return 0;
}
