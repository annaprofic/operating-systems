CFLAGS  := -O2 -Wall -c
CC := gcc
RM := rm -f

.PHONY: all clean

NAME1 := pet
OBJ1 := $(NAME1).o
NAME1 := case
OBJ1 := $(NAME1).o


#-----------------------------------------------------------------------------------------

all: libshmem.so pet.x case.x

#=========================================================================================
#	Tworzenie biblioteki wlasnej 	*dynamiczna*
#=========================================================================================

shmem.o: shmem.c
	gcc -std=c99 -c -O -fPIC shmem.c

libshmem.so: shmem.o
	gcc -std=c99 -shared -o libshmem.so shmem.o

#-----------------------------------------------------------------------------------------

	export LD_LIBRARY_PATH=. 

%.x: %.o libshmem.so
	$(CC) -std=c99 -L. -lshmem -o $@ $^ -Wl,-rpath .

%.o: %.c
	$(CC) -std=c99 $(CFLAGS) -o $@ $<

#-----------------------------------------------------------------------------------------

clean:
	$(RM) *.o *.x *.so
