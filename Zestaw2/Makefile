#Definicja zmiennych z opcjami kompilatora/linkera
CFLAGS  := -O2 -Wall
CC := gcc

#Dyrektywa ktora mowi ze dane regula nie jest nazwa pliku
.PHONY: all clean

#Regula domyslna ktora kompiluje wszystkie programy
all: obsluga.x wysylaj.x grupa.x

#Definicje zaleznosci
obsluga.x: obsluga.o
wysylaj.x: wysylaj.o
grupa.x: grupa.o

obluga.o: obsluga.c
wysylaj.o: wysylaj.c
grupa.o: grupa.c

#Cele i zaleznosci mozemy zastapic zmiennymi automatycznymi dla optymalizacji zapisu
%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Regula, ktora usuwa pliki tymczasowe i wykonywalne
clean:
	$(RM) *.o *.x
