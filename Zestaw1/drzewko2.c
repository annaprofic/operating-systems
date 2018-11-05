#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "procinfo.h" /* plik naglowkowy */
int dzieci = 0; /* zmienna ktora liczy ilosc dzieci */
int i = 0;

int main(int argc, char *argv[]) {
	printf("\n");
	procinfo("TREE2");

	for (i = 0; i < 3; i ++) {
		switch (fork()) {
			case -1: /* fork zwraca wartosc -1 ktora oznacza porazke */
								/* Powodem moze byc brak pamieci lub przekroczenie limitu na liczbe procesow */
	      perror("Nowego procesu potomnego nie da sie utworzyc.\n");
	      exit(0);
				break;
			case 0: /* kiedy istnieje proces potomny - wypisuje id procesow */
	      strncpy(argv[0], "Child", strlen(argv[0]));
				procinfo(argv[0]);
	      break;
			default:
	      dzieci ++; /* musimy policzyc ile procesow potomnych sie tworza, aby pozniej proces miecierzysty czekal potrzebna ilosc razy */
	      strcpy(argv[0], "Parent");
				break;
	  }
	  if (dzieci != 0 ) { /* jezeli ilosc procesow potomnych rozni sie od zera to prosec macierzysty czeka */
	    wait(NULL); /* wylolanie znajduje sie w petli wiec odbedzie sie potrzebna ilosc razy */
	    break;
	  }
	}
	return (0);
}
