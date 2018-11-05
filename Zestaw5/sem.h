#ifndef PROCINFO_H
#define PROCINFO_H
// plik naglowkowy gdzie miesci sie interfejs modulu - deklaracja funkcji

int semDecl(int id, int semnum);
void semInit(int semid, int semnum, int val);
void semRm(int semid, int semnum);
void semP(int semid, int semnum);
void semV(int semid, int semnum);
void semZ(int semid);
void semInfo(int semid);
#endif
