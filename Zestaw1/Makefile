#Definicja zmiennych z opcjami kompilatora/linkera
CFLAGS  := -O2 -Wall
CC := gcc

#Dyrektywa ktora mowi ze dane regula nie jest nazwa pliku
.PHONY: all clean

#Regula domyslna ktora kompiluje wszystkie programy
all: procesy.x kopiuj.x drzewko1.x drzewko2.x potomny.x macierzysty.x 

#Definicje zaleznosci
kopiuj.x: kopiuj.o
procesy.x: procesy.o procinfo.o
drzewko1.x: drzewko1.o procinfo.o
drzewko2.x: drzewko2.o procinfo.o
potomny.x: potomny.o procinfo.o
macierzysty.x: macierzysty.o procinfo.o


kopiuj.o: kopiuj.c
procesy.o: procesy.c procinfo.h
procinfo.o: procinfo.c procinfo.h
drzewko1.o: drzewko1.c procinfo.h
drzewko2.o: drzewko2.c procinfo.h
potomny.o: potomny.c procinfo.h
macierzysty.o: macierzysty.c procinfo.h


#Cele i zaleznosci mozemy zastapic zmiennymi automatycznymi dla optymalizacji zapisu
%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Regula, ktora usuwa pliki tymczasowe i wykonywalne
clean:
	$(RM) *.o *.x
