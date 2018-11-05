#include <signal.h> /* sygnaly */
#include <sys/types.h>
#include <stdlib.h> /* atoi */
#include <unistd.h> /* getpid */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int procinfo(const char *name) { /* Wypisywanie komunikatu (za pomaca f-cji systemowych) w ktorym podana jest informacja o procesie */
  printf("%s: User ID: %d, Process ID: %d, Parent process ID: %d, Group ID: %d, Process group ID: %d.\n",
  name, (int)getuid(),(int)getpid(), (int)getppid(), (int)getgid(), (int)getpgrp());
  return 0;
}

int main(int argc, char const *argv[]) {
    int i = 0;
    char * argv1[argc];
    const char * akcja = argv[1];
    int sygnal = atoi(argv[2]);

    for (i = 0; i < argc; i ++ ) { /* alokowanie pamieci dla tablicy argv1 */
      argv1[i] = malloc(sizeof(argv[0]));
    }

    for (i = 0; i < argc; i ++ ) { /* kopiowanie argumentow programu do stworzonej tablicy */
      strcpy(argv1[i], argv[i]);
    }

    if (argc != 3 ) {
      printf("Niepoprawna ilosc argumentow.\n");
      printf("Prosze wpisac komende:\n./grupa.x 'rodzaj akcji: ('d','i' lub 'p')' 'numer sygnalu'.\n");
      return 1;
    }
    procinfo ("\nParent");
    printf("\n");
    for (i = 0; i < 3; i ++) {
    switch (fork()) {

			case -1: 	/* fork zwraca wartosc -1 ktora oznacza porazke */
		     perror("Nowego procesu potomnego nie da sie utworzyc.\n");
		 		 exit(0);
			 	 break;
			case 0: /* przechodzenie do obslugi sygnalu, odczytywanie sposobu dzialania sygnalu */
         execl("./obsluga.x", "./obsluga.x", akcja, argv1[2], NULL);
				 exit(0);
				 break;
  		default:
         break;
		}
    sleep(3);
  }
  signal(sygnal , SIG_IGN);
  printf ("Sygnal %d wyslany...\n", sygnal);
  sleep (3);
  kill(0, 0); /* test bledow dla grupy procesow */
  if (errno != ESRCH) { /* jesli grupa procesow istneje */
  kill(0, sygnal); /* wysylanie sygnalow */ 
  }
  else printf("Blad wysylania sygnalow do procesow.\n");
  for (i = 0; i < argc; i ++ ) { /* zwalnanie pamieci tablicy */
    free(argv1[i]);
  }
  wait(NULL);
  return 0;
}
