
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40
#define KEY 647
int main() {
key_t key = KEY;
size_t size = SIZE;
int shmid;
char *shm;
char string[SIZE];

shmid = shmget(key, size, IPC_CREAT | 0666);
if (shmid == -1) {
perror("shmget");
exit(1);
}

shm = (char*)shmat(shmid, NULL, 0);
if (shm == (char*)-1) {
perror("shmat");
exit(1);
}
printf("Server: Enter the message: ");
if (fgets(string, SIZE, stdin) == NULL) {
perror("fgets");
exit(1);
}
string[strcspn(string, "\n")] = 0; 

strcpy(shm, string);
printf("Server: Message written to memory\n");

shmdt(shm);
return 0;
}

