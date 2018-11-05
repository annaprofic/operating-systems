#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "procinfo.h" /* plik naglowkowy deklaracja funkcji */
int i = 0;

int main(int argc, char *argv[]) {
	printf("\n");
	procinfo("TREE1"); /* wywolanie procesu miecierzystego, od ktorego tworzymy dzieci */
	
	for (i = 0; i < 3; i ++) {
		switch (fork()) {
			case -1: 	/* fork zwraca wartosc -1 ktora oznacza porazke */
								/* Powodem moze byc brak pamieci lub przekroczenie limitu na liczbe procesow */
	    	perror("Nowego procesu potomnego nie da sie utworzyc.\n");
	      exit(0);
				break;
			case 0: 	/* kiedy istnieje proces potomny - wypisuje id procesow */
				strncpy(argv[0], "Child", strlen(argv[0]));
				procinfo(argv[0]);
				goto koniec_drzewka; /* po wykonaniu tworzenia procesow potomnych musimy wyjsc z petli oby fork dalej nie tworzy dzieci*/
			default: 	/* wywolanie procesu macierzystego */
				strcpy(argv[0], "Parent");
				break;
		}
	}
	koniec_drzewka: /* etykieta dla goto */
	/* funkcja czeka na zakonczenie pierwszego procesu potomnego */
	/* proces miacierzysty tworzy trzy procesy potomne wiec wywolujemy f-cje trzy razy */
		wait(NULL);
		wait(NULL);
		wait(NULL);
	return (0);
}
