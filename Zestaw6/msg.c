#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg.h"

int msgCreate(int id) {

    key_t key;
    int msgid = 0; 
    if ((key = ftok(".", id)) == -1 ) { 
        perror("error key\n");
        exit(EXIT_FAILURE);
    }

    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) { 
        perror ("error msgget msgCreate\n");
        exit (EXIT_FAILURE);
    }
    
    return msgid;
}

void msgRm(int msgid) {
    printf("Usuwam kolejke...\n");
    if (msgctl(msgid, IPC_RMID, NULL) == -1) { 
        perror ("error mgsRm\n"); 
        exit(EXIT_FAILURE); 
    }
    
}

void msgSend(int msgid, komunikat *msg) {

    //if (msgsnd(msgid, msg, sizeof(komunikat), 0) == -1 ){ 
    //    perror("error msgSend\n");
    //    exit(EXIT_FAILURE);
    //}
    msgsnd(msgid, msg, sizeof(komunikat), 0);
    
}    

void msgRecv(int msgid, komunikat *msg, int mtype) {

    //if (msgrcv(msgid, msg, sizeof(komunikat) , mtype, 0) == -1) {
    //    perror("error msgRecv\n");
    //    exit(EXIT_FAILURE); 
    //}
    msgrcv(msgid, msg, sizeof(komunikat) , mtype, 0);
    
}

void msgInfo(int msgid) {

    struct msqid_ds buf; 
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
          perror("error msgInfo\n");
          exit(EXIT_FAILURE);
    }
    printf ("Informacja o MSG:\n");
    printf ("Ilosc komunikatow: %lu\nMozliwa ilosc bajtow: %lu\nPID_1: %d\nPID_2: %d\n", buf.msg_qnum, buf.msg_qbytes, buf.msg_lspid, buf. msg_lrpid);
}