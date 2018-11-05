#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "procinfo.h" /* plik naglowkowy gdzie miesci sie interfejs modulu - deklaracja funkcji*/
int i = 0;

int main(int argc, char *argv[]) {
	printf("\n");
	procinfo("Parent"); /* wywolanie id prosecow macierzystych */

	for (i = 0; i < 3; i ++) {
		switch (fork()) {

			case -1: 	/* fork zwraca wartosc -1 ktora oznacza porazke */
						 		/* Powodem moze byc brak pamieci lub przekroczenie limitu na liczbe procesow */
		     perror("Nowego procesu potomnego nie da sie utworzyc.\n");
		 		 exit(0);
			 	 break;

			case 0: 	/* zwraca 0*/
								/* kiedy istnieje proces potomny, wipisujemy id za ponoca proinfo */
				 strncpy(argv[0], "Child", strlen(argv[0]));
			 	 procinfo(argv[0]);
				 sleep(1); /* sleep wykorzystujemy dla wstrzymania wywolujacego procesu. */
				 break;

			default: 	/* id procesu dziecka - jakas liczba naturalna wieksza od zera - w rodzicu */
								/* proces macierzysty */
				 strcpy(argv[0], "Parent");
				 break;
		}
	}
	sleep(2); /* Za pomoca sleep'ow grupujemy procesy */
						/* usypianie procesow tworzonych fork'iem */
						/* proces musi poczekac az kazdy inny proces jego pokolenia sie utworzy */
	return (0);
}
