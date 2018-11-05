#ifndef MSG_H
#define MSG_H

typedef struct msgbuf {  
    long mtype;  //typ komunikatu 
    long pid_klienta;  
    char tekst[256];  // tekst komunikatu 
} komunikat;

int msgCreate(int id);
void msgRm(int msgid) ;
void msgSend(int msgid, komunikat *msg);
void msgRecv(int msgid, komunikat *msg, int mtype);
void msgInfo(int msgid);

#endif