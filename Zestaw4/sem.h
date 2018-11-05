#ifndef SEM_H
#define SEM_H
// plik naglowkowy gdzie miesci sie interfejs modulu - deklaracja funkcji */

int semDecl(int id);
void semInit(int semid, int val);
void semRm(int semid);
void semP(int semid);
void semV(int semid);
void semZ(int semid);
void semInfo(int semid);
#endif
