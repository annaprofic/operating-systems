#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "msg.h"

int sygnal = 2;
int running = 1; 

void przerwanie(int sygnal) {  // funkcja ktora przerywa petle, usuwajac kolejke 
    printf("\nPrzerwanie...\n");
    running = 0; 

}

int main(int argc, char const *argv[]) {

    if (argc != 1) { 
        perror("Nieprawidlowa ilosc argumentow!\n");
        exit(EXIT_FAILURE);
    }
    
    int id; 
    int i = 0;
    komunikat msg; 

    printf("Tworze kolejke...");
    sleep(2);
    int msgid = msgCreate(1); 
    printf("Kolejka zostala utworzona! MSG ID: %d\n", msgid);

    if (signal(sygnal, przerwanie) == SIG_ERR) { // przechwycenie obslugi sygnalu sigint, wykonanie wlasnej funkcji 
            perror("Wystapil blad. Funkcja nie moze wykonac operacje.");
            exit(EXIT_FAILURE);
    }

    while (running != 0) {

        msgRecv(msgid, &msg, 1); // Serwer tym czasem czeka na wyslana przez klienta wiadomosc typu 1. 
		//otrzymujac ja on powieksza kazda litere.

        printf("Odebrany komunikat od (%ld): %s \n", msg.pid_klienta, msg.tekst); 
        sleep(1); 
        // Typ ustala sie na PID klienta ( przechowywany w strukturze ) i wysyla sie
		// kolejka komunikatu z powrotem do klienta. 
        id = msg.pid_klienta; 
        msg.mtype = id; 

        i = 0; 

        while(msg.tekst[i] != '\0') {
            msg.tekst[i] = toupper(msg.tekst[i]);
            i ++;
        }

        msgSend(msgid, &msg); 
    }

    msgRm(msgid); // po ustaleniu running na 0 przerywa sie petla, kolejka sie usuwa
    return 0;
}