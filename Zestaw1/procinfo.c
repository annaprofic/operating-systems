#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "procinfo.h" /* plik naglowkowy gdzie miesci sie interfejs modulu */

int procinfo(const char *name) { /* Wypisywanie komunikatu (za pomaca f-cji systemowych) w ktorym podana jest informacja o procesie */
	printf("Name: %s, User ID: %d, Process ID: %d, Parent process ID: %d, Group ID: %d, Process group ID: %d.\n",
	name, (int)getuid(),(int)getpid(), (int)getppid(), (int)getgid(), (int)getpgrp());
	return 0;
	}
