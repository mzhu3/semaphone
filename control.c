#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>

union semun{
  int value;
  struct semid_ds *buf;
  unsigned long *buffer;
  struct seminfo *_buf;
};

int main(int argc, char *argv[]){
  char command[256];
  int sc;
  int meme = shmget(24333, sizeof(char), IPC_CREAT | 0644);
  if(strncmp(argv[1], "-c", strlen(argv[1]))==0){
    int semid = semget(ftok("story.txt",256),1, IPC_CREAT| 0644);
    open("story.txt", O_TRUNC | O_CREAT, 0644);
    printf("semaphore created, storytxt created\n");
    union semun su;
    su.value = 1;
    sc = semctl(semid,0,SETVAL,su);
  }
  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
    int  semid = semget(ftok("story.txt",256), 1, 0);
    sc = semctl(semid, 0, GETVAL);
    printf("semaphore value: %d\n",sc);
    char *s[100] = {"cat","story.txt"};
    execvp(s[0],s);

  }
  else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
    int semid = semget(ftok("story.txt",256), 1, 0);
    sc = semctl(semid, 0, IPC_RMID);
    printf("semaphore removed: %d\n", sc);
    char *s[100] = {"cat","story.txt"};
    execvp(s[0],s);
  }

  
  return 0;
}
