#ifndef SHMEM_H
#define SHMEM_H
// plik naglowkowy gdzie miesci sie interfejs modulu - deklaracja funkcji */

int shmCreate(int id, int size);
int shmOpen(int id);
void shmRm(int shmid);
void* shmAt(int shmid);
void shmDt(void *adres);
int shmSize(int shmid);
void shmInfo(int shmid);

#endif
