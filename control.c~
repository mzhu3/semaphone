#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>
union semun{
  int value;
  struct semid_ds *buf;
  unsigned long *buffer;
  struct seminfo *_buf;
};

int main(){
  char command[256];
  int sc;
  fgets(command,sizeof(command),stdin);
  int semid = semget(ftok("story.txt",256),1, IPC_CREAT| 0644);
  open("story.txt", O_TRUNC | O_CREAT, 0644);
  union semun su;
  su.value = 1;
  sc = semctl(semid,0,SETVAL,su);
  
  return 0;
}
