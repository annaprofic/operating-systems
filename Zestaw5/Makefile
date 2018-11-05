CFLAGS  := -O2 -Wall -c
CC := gcc
RM := rm -f

NAME1 := shmuse
NAME2 := glowny

OBJ1 := $(NAME1).o
OBJ2 := $(NAME2).o

EXEC1d1 := $(NAME1)1.x
EXEC1d2 := $(NAME1)2.x



.PHONY: all clean

#-----------------------------------------------------------------------------------------

all: libshmem.so libsem.a producent.x konsument.x glowny.x shmuse1.x shmuse2.x

#=========================================================================================
#	Tworzenie biblioteki wlasnej 	*dynamiczna*
#=========================================================================================

shmem.o: shmem.c
	gcc -std=c99 -c -O -fPIC shmem.c

libshmem.so: shmem.o
	gcc -std=c99 -shared -o libshmem.so shmem.o

#=========================================================================================
#	Tworzenie biblioteki wlasnej 	*statyczna*
#=========================================================================================

sem.o: sem.c
	gcc $(CFLAGS) -c sem.c

libsem.a: sem.o
	ar rv libsem.a sem.o

#-----------------------------------------------------------------------------------------

$(EXEC1d1): $(OBJ1) libshmem.so
	$(CC) -std=c99 -L. -lshmem -o $@ $^ -Wl,-rpath .

$(EXEC1d2): $(OBJ1) libshmem.so
	$(CC) -std=c99 -L. -lshmem -o $@ $^
	export LD_LIBRARY_PATH=. 


%.x: %.o libshmem.so libsem.a
	$(CC) -std=c99 -L. -lshmem -lsem -o $@ $^ -Wl,-rpath .

%.o: %.c
	$(CC) -std=c99 $(CFLAGS) -o $@ $<

#-----------------------------------------------------------------------------------------

clean:
	$(RM) *.o *.x *.so *.a
