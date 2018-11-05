#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "procinfo.h" /* plik naglowkowy gdzie miesci sie interfejs modulu */

int main(int argc, char * argv[] ) {
	procinfo(argv[0]); /* polecenie - musimy tylko wylolac funkcje procinfo() */
	return 0;
}
