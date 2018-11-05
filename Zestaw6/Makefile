CFLAGS  := -O2 -Wall -c
CC := gcc
RM := rm -f

.PHONY: all clean

NAME1 := klient
OBJ1 := $(NAME1).o
NAME2 := serwer
OBJ1 := $(NAME1).o


#-----------------------------------------------------------------------------------------

all: libmsg.so libmsg.a serwer.x klient.x

#=========================================================================================
#	Tworzenie biblioteki wlasnej 	*dynamiczna*
#=========================================================================================

msg.o: msg.c
	gcc -std=c99 -c -O -fPIC msg.c

libmsg.so: msg.o
	gcc -std=c99 -shared -o libmsg.so msg.o

#=========================================================================================
#	Tworzenie biblioteki wlasnej 	*statyczna*
#=========================================================================================

libmsg.a: msg.o
	ar rv libmsg.a msg.o

#-----------------------------------------------------------------------------------------	

	export LD_LIBRARY_PATH=. 

%.x: %.o libmsg.so libmsg.a
	$(CC) -std=c99 -L. -lmsg -o $@ $^ -Wl,-rpath .

%.o: %.c
	$(CC) -std=c99 $(CFLAGS) -o $@ $<

#-----------------------------------------------------------------------------------------

clean:
	$(RM) *.o *.x *.so *.a
