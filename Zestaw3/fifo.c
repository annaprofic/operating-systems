#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char * potokfifo;
int main (int argc, char const *argv[]) {

      if (argc == 1) {
            potokfifo = "potokfifo";
      }
      if (argc == 2) {
            potokfifo = argv[1];
      }
      if (argc != 1 && argc != 2) { //sprawdzanie poprawnie zapisanej komendy przy uruchamianiu 
            printf("Niepoprawna ilosc argumentow. Prosze uruchomic program poorawnie: ./fifo.x lub ./fifo.x 'nazwa potoku'\n");
            exit(1);
      }

      if ( mkfifo(potokfifo, 0666) == -1 ) { // tworzenie potoku nazwanego z standartowym dostepem chmod 666 dla wszystkich bez wykonywania 
            perror("Blad funkcji tworzacej potok.\n");
            exit(1);
      }

          switch (fork()) {
            case -1:
                  perror ("Nie udalo sie stworzyc procesu potomnego");
                  exit(1);
            case 0:
                  execl("./konsument.x","./konsument.x", potokfifo,  NULL); // uruchamianie funkcji z konsument.c
                  break;
            default:
                  switch (fork()) {
                        case -1:
                              perror ("Nie udalo sie stworzyc procesu potomnego");
                              exit(1);
                        case 0:
                              execl("./producent.x","./producent.x", potokfifo,  NULL); // uruchamianie funkcji z producent.c
                              break;
                        default:
                              wait (NULL); // proces macierzysty czeka na proces potomny 
                        break;
                  }

            wait (NULL);
            unlink(potokfifo); // usuwanie pliku stworzonego kolejka mkfifo
            system("diff -s magazyn.txt schowek.txt"); // porownywanie plikow 
            break;
          }
    return 0;
}
