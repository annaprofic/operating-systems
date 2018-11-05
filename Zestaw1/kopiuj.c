#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define buffrozmiar 128 /* zmienna stala dla rozmiaru buffora */
char buffer[128];

int main(int argc, char* argv[]) {
  int fd_o, fd_copy, zamykanie_1, zamykanie_2;
  ssize_t b_read, b_write; /* wykorzystamy dla funkcji ktora moze przyjac wartosc -1, co znaczy blad */
    if(argc != 3) { /* sprawdzanie poprawnosci wpisanych prze uzytkownika argomentow pragramu*/
        printf ("Niepoprawna ilosc argumentow. Program musi zawierac trzy argumenty.\n");
        printf ("Prosze o poprawnym wpisaniu komendy:\n./nazwa programu 'plik zrodlowy.rozszerzenie' 'plik docelowy.rozszerzenie'.\n");
        return 1;
      }
  fd_o = open(argv[1], O_RDONLY | O_CREAT); /* Otwieranie pliku, ktory bedzie skopiowany */
  /* plik tylko do odczytu w przypadku gdy nie istnieje - bedzie stworzony za pomoca O_CREAT */
    if (fd_o == -1) { /* sprawdzanie poprawnosci funkcji otwierania */
        perror ("Nie mozna otworzyc plik zrodlowy.f\n");
        exit (1);
      }
  /* Otwieranie lub tworzenie kopii pliku */
  fd_copy = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fd_copy == -1) {
        perror("Nie mozna otworzyc plik docelowy.\n");
        exit(1);
      }
  /* wczytywanie i zapisywanie bajtow */
  while ((b_read = read(fd_o, &buffer, buffrozmiar)) > 0) {
    b_write = write(fd_copy, &buffer, (ssize_t)b_read);
      if( b_write != b_read) { /* gdy ilosc wczytatych i wpisanych bajtow sie rozni - oznacza ze funkcja dziala niepoprawnie*/
        perror("Niepoprawne wczytywanie lub wpisanie bajtow.\n");
        exit(1);
      }
  }
  printf("Plik %s zostal skopiowany do pliku %s.\n", argv[1], argv[2]);
  /* zamykanie plikow */
  zamykanie_1 = close(fd_o);
  if ( zamykanie_1 == -1) { /* sprawdzanie wykonania funkcji zamykania pliku */
    perror ("Wystapil blad przy zamykniu pliku zrodlowego.\n");
  }
  zamykanie_2 = close(fd_copy);
  if ( zamykanie_2 == -1) {
    perror ("Wystapil blad przy zamykaniu pliku docelowego.\n");
  }

  return (0);
}
