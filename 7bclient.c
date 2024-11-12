#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SHM_KEY 647 
#define SHM_SIZE 40 
int main() {
int shm_id;
char *shm_addr;

shm_id = shmget(SHM_KEY, SHM_SIZE, 0);
if (shm_id == -1) {
perror("shmget");
exit(1);
}

shm_addr = shmat(shm_id, NULL, 0);
if (shm_addr == (char *) -1) {
perror("shmat");
exit(1);
}

printf("Client: Received message from shared memory: %s\n", shm_addr);

shmdt(shm_addr);
return 0;
}

