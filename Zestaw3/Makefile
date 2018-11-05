#Definicja zmiennych z opcjami kompilatora/linkera
CFLAGS  := -O2 -Wall
CC := gcc

#Dyrektywa ktora mowi ze dane regula nie jest nazwa pliku
.PHONY: all clean

#Regula domyslna ktora kompiluje wszystkie programy
all: prodkons.x konsument.x producent.x fifo.x

#Definicje zaleznosci
prodkons.x: prodkons.o 
konsument.x: konsument.o 
producent.x: producent.o 
fifo.x: fifo.o

prodkons.o: prodkons.c
konsument.o: konsument.c
producent.o: producent.c
fifo.o: fifo.c

#Cele i zaleznosci mozemy zastapic zmiennymi automatycznymi dla optymalizacji zapisu
%.x: %.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Regula, ktora usuwa pliki tymczasowe i wykonywalne
clean:
	$(RM) *.o *.x
