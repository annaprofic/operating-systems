#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int i = 0;
    char * argv1[argc];
      if (argc != 3) {
      		printf ("Niepoprawna ilosc argumentow.\n");
          printf("Prosze wpisac komende:\n./wysylaj.x 'rodzaj akcji: ('d','i' lub 'p')' 'numer sygnalu'.\n");
      		return 1;
      }
      const char * akcja = argv[1];
      int sygnal = atoi(argv[2]);
      int pid;
      for (i = 0; i < argc; i ++ ) { /* alokowanie pamieci dla tablicy argv1 */
    		argv1[i] = malloc(sizeof(argv[0]));
    	}

      for (i = 0; i < argc; i ++ ) { /* kopiowanie argumentow programu do stworzonej tablicy */
    		strcpy(argv1[i], argv[i]);
    	}

    		switch (pid = fork()) {
    			case -1: /* fork zwraca wartosc -1 ktora oznacza porazke */
    						 	 /* Powodem moze byc brak pamieci lub przekroczenie limitu na liczbe procesow */
                    perror("Nowego procesu potomnego nie da sie utworzyc.\n");
                    exit(0);
                    break;
    			case 0: /* przedchodzenie do obslugi procesow */
                    execl("./obsluga.x", "./obsluga.x", akcja, argv1[2], NULL);
                    exit (0);
                    break;
    			default:
                    printf ("Sygnal %d wyslany dla process id: %d...\n", sygnal, pid);
                    sleep (2);
                    kill(pid, 0); /* wykonujemy test bledow */
                    if (errno != ESRCH) { /* w przypadku, gdzy proces istneje */
                    kill(pid, sygnal); /* wysylanie sygnalu do procesu */
                    }
                    else printf("Blad wysylania sygnalow do procesow.\n");
                    break;
    			}
                sleep(2);
      for (i = 0; i < argc; i ++ ) { /* zwalnanie pamieci tablicy */
        free(argv1[i]);
      }
    	return (0);
}
