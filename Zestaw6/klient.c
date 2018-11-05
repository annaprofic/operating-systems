#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg.h"
#define MAX 256

int main(int argc, char const * argv[]) {

    if (argc != 1) { 
        perror("Nieprawidlowa ilosc argumentow!\n");
        exit(EXIT_FAILURE);
    }
    
    char wpisanedane[MAX]; 
    komunikat msg; 
    printf("Uzyskuje dostep..."); 
    sleep(2);
    int msgid = msgCreate(1); 
    printf ("Dostep zostal uzyskany! MSG ID: %d\n", msgid); 
 
    printf ("Wpisz wiadomosc do serwera: ");   // klient pobiera dane, ktore wpisuje uzytkownik z stdin 
    //i umieszcza do komunikatu
    fgets( wpisanedane, MAX, stdin);
    strncpy(msg.tekst, wpisanedane, MAX);

    printf ("Komunikat wpisany i wyslany DO SERWERA: %s\n", msg.tekst);

    msg.pid_klienta = (int)getpid(); //Pobiera sie pid procesu i zapisuje sie do drugiego argumentu struktury komunikatu  
    msg.mtype = 1;   // typ ustalony na 1, bo procesu z takim PID nie bedzie istniec w programie, poniewaz tym procesem jest init
    // umozliwia odebranie komunikatu tylko serwerem 

    printf ("   Klient pid: (%ld)\n", msg.pid_klienta); 
    printf ("   mtype: %ld\n", msg.mtype );

    msgSend(msgid, &msg); 

    msgRecv(msgid, &msg, msg.pid_klienta); // odbior klienta jest ustalony na typ - swoj PID.

    printf("\nKomunikat otrzymany OD SERWERA: %s\n", msg.tekst);

    return 0;
}