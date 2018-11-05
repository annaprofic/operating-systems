#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "procinfo.h" /* plik naglowkowy (deklaracja funkcji procinfo()) */
int i = 0;

int main(int argc, char *argv[]) {
	char * argv1[argc]; /* tworzymy tablice do przehowywania argumentow */
	printf("\n");

	for (i = 0; i < argc; i ++ ) { /* alokowanie pamieci dla tablicy argv1 */
		argv1[i] = malloc(strlen(argv[i])+1);
	}
	for (i = 0; i < argc-1; i ++ ) { /* kopiowanie argumentow programu do stworzonej tablicy */
		strcpy(argv1[i], argv[i+1]);
	}
	argv1[i] = NULL;
	procinfo (argv[0]);
	for (i = 0; i < 3; i ++) {
		switch (fork()) {
			case -1: /*fork zwraca wartosc -1 ktora oznacza porazke */
						 	 /* Powodem moze byc brak pamieci lub przekroczenie limitu na liczbe procesow */
			      perror("Nowego procesu potomnego nie da sie utworzyc.\n");
			      exit(0);
				  break;
			 case 0:
			  	  sleep(4);/* kiedy istnieje proces potomny - wypisuje id procesow. */
				  execv(argv1[0], argv1);
				  exit(0);
				  break; /* musimy wskazac na program dla inicjalizacji nowego procesu */
							 /* 'v' na koncu wskazuje nam ze korzystamy z tablicy argumentow */
			default: /* nie jest koniecznym wpisania funkcji do default to uzywaniu f-cji systemowej rodziny exec */
				  break;
			}
			sleep(1);
	}
	sleep (4);
	
	for (i = 0; i < argc-1; i ++ ) { /* zwalnanie pamieci tablicy */
		free(argv1[i]);
	}
	return (0);
}
