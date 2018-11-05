#Definicja zmiennych z opcjami kompilatora/linkera
CFLAGS  := -O2 -Wall
CC := gcc

#Dyrektywa ktora mowi ze dane regula nie jest nazwa pliku
.PHONY: all clean

#Regula domyslna ktora kompiluje wszystkie programy
all: libsem.a semuse.x powielacz.x prog.x

#Tworzenie biblioteki wlasnej 
sem.o: sem.c
	gcc $(CFLAGS) -c sem.c

libsem.a: sem.o
	ar rv libsem.a sem.o

#Definicje zaleznosci

semuse.x: semuse.o 
powielacz.x: powielacz.o 
prog.x: prog.o

semuse.o: semuse.c sem.h
powielacz.o: powielacz.c
prog.o: prog.c


#Cele i zaleznosci mozemy zastapic zmiennymi automatycznymi dla optymalizacji zapisu
%.x: %.o
	$(CC) -L. -lsem -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

#Regula, ktora usuwa pliki tymczasowe i wykonywalne
clean:
	$(RM) *.o *.x *.a
