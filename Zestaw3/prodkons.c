#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

char *buffor;
ssize_t file_write, file_read;
FILE *file1, *file2;

void konsument(int filedes[]) {
      // zamykamy deskryptor do zapisu
      close(filedes[1]); 

      buffor = malloc(128);

      file2 = fopen("schowek.txt", "w"); // otwieranie pliku w trybie write - do zapisu
      if ( file2 == NULL ) {
            perror("Plik 'schowek.txt' nie udalo sie otworzyc.");
            exit(1);
      }

      while ((file_read = read(filedes[0], buffor, 128)) > 0 ) { // jak nie ma wiecej procesow - procesy ktore czekaly na odczyt z potoku zostaja obudzone
            usleep(rand() % 2000000); //usypanie z liczbami randomowymi 
            printf("  --> Konsument %s\n", buffor);
            fputs(buffor, file2); //wpisywanie po kolei elementow z bufora
      }

      if (fclose(file2) != 0 ) { //zamykanie pliku do zapisu 
            perror ("Plik 'schowek.txt' nie udalo sie zamknac");
            exit(1);
      }
      if (close(filedes[0]) == -1) { // zamykanie deskryptora odczytu
            perror ("Blad przy zamykaniu deskryptora wejscia.");
            exit(1);
      }
}

void producent (int filedes[]) {
      // zamykamy deskryptor do odczytu 
      buffor = malloc(128);
      close(filedes[0]);

      file1 = fopen("magazyn.txt", "r"); // otwieranie oliku w trybie read - do odczytu
      if ( file1 == NULL ) {
            perror("Plik 'magazyn.txt nie udalo sie otworzyc'.");
            exit(1);
      }

      while (!(feof(file1))) {
            fgets(buffor, 128, file1);
            usleep(rand() % 2000000);
            file_write = write(filedes[1], buffor, 128);  //gdy zaden proces nie czyta, do wszystkich procesow czekajacych na zapis wysyla sie sigpipe.
            printf("Producent --> %s\n", buffor);
            
            if (file_write == -1 ) { // test bledow
                  perror("Blad przesylania danych do Konsumenta.\n");
                  exit(1) ;
            }
      }

      if (fclose(file1) != 0 ) { // zamykanie pliku do odczytu
            perror ("Plik 'magazyn.txt' nie udalo sie zamknac");
            exit(1);
      }
      if (close(filedes[1]) == -1) { // zamykanie deskryptora zapisu 
            perror ("Blad przy zamykaniu deskryptora wyjscia.");
            exit(1);
      }

}

int main (int argc, char const *argv[]) {
      srand(time(0));
      int filedes[2];

      if ( pipe(filedes) == -1 ) { // funkcja tworzaca potok nienazwany
            perror("Blad funkcji tworzacej potok.\n"); // test bledow
            exit(1);
      }

      switch (fork()) {
            case -1:
                  perror ("Nie udalo sie stworzyc procesu potomnego");
                  exit(1);
            case 0:
                  konsument(filedes); /* proces potomny - konsument */ //read fput
                  break;
            default:
                  producent(filedes);
                  wait (NULL); /* proces macierzysty - producent */ //fopen fgets write
                  printf("\n");
                  execl ("/bin/sh", "sh", "-c", "diff -s magazyn.txt schowek.txt", NULL);
            break;
      }
return 0;
}
