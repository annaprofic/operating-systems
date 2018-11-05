#include <signal.h> /* sygnaly */
#include <sys/types.h>
#include <stdlib.h> /* atoi */
#include <unistd.h> /* getpid */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wlasna_funkcja( int sygnal) { /* opis wlasniej funkcji uzytkownika */
  printf("\nSygnal %d o pid = %d zostal obsluzony.\n", sygnal, getpid());
}

int main(int argc, char const *argv[]) {
  int sygnal = 0;
  int ak = 12;
  const char * akcja = argv[1];
  sygnal = atoi(argv[2]);

  if (argc != 3 ) { /* sprawdzanie poprawnej ilosci argumentow */
    printf("Niepoprawna ilosc argumentow.\n");
    printf("Prosze wpisac komende:\n./obsluga.x 'rodzaj akcji: ('d','i' lub 'p')' 'numer sygnalu'.\n");
    return 1;
  }
  printf("Process info: User ID: %d, Process ID: %d, Parent process ID: %d, Group ID: %d, Process group ID: %d.\n",
  (int)getuid(),(int)getpid(), (int)getppid(), (int)getgid(), (int)getpgrp());

  /* przyjmowanie argumentu programu, ktory odpowiada za operacje, w jaki sposob przyjmujemy sygnal)*/
  if (strcmp( akcja, "d") == 0)  ak = 0;
  if (strcmp( akcja, "i") == 0)  ak = 1;
  if (strcmp( akcja, "p") == 0)  ak = 2;

    switch (ak) {
      case 0:
        printf("Akcja: Wykonanie operacji domyslnej sygnalu...\n");
          if (signal(sygnal , SIG_DFL) == SIG_ERR) {
            perror("Wystapil blad. Funkcja nie moze wykonac operacji domyslnej.");
        }
        break;
      case 1:
        printf("Akcja: Ignorowanie sygnalu.\n");
          if (signal(sygnal , SIG_IGN) == SIG_ERR) {
            perror("Wystapil blad. Funkcja nie moze zignorowac sygnal...\n");
        }
        break;
      case 2:
        printf("Akcja: Przechwycenia i wlasna obsluga sygnalu...\n");
          if (signal(sygnal , wlasna_funkcja) == SIG_ERR) {
            perror("Wystapil blad. Funkcja nie moze wykonac operacje.");
        }
        break;
      default:
        printf("Prosze podac rodzaj akcji. 'd' - domyslna operacja, 'i' - igorowanie, 'p' - przechwycenie.\n");
        exit(1);
    }
  pause();
  return 0;
}
