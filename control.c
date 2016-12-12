#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

union semun{
  int value;
  struct semid_ds *buf;
  unsigned long *buffer;
  struct seminfo *_buf;
};

int main(int argc, char *argv[]){
  int sc,semid,meme,meid;
  if(strncmp(argv[1], "-c", strlen(argv[1]))==0){
    semid = semget(ftok("story.txt",256),1, IPC_CREAT| 0644);
    meme = shmget(ftok("control.c",256),1000, IPC_CREAT | IPC_EXCL | 0644);
    int  f = open("story.txt", O_TRUNC | O_CREAT, 0644);
    union semun su;
    su.value = 1;
    sc = semctl(semid,0,SETVAL,su);
    if(semid == -1){
      printf("Bro. We got it\n");
      exit(0);
    }
    printf("Shared memory id: %d\n",meme);
    printf("semaphore id: %d\n",semid);
    printf("semaphore created, storytxt created, shared memory created \n");
    close(f);
  }
  else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){
    semid = semget(ftok("story.txt",256), 1, 0);
    sc = semctl(semid, 0, GETVAL);
    int f = open("story.txt",O_RDONLY,0644);
    char buffer[100000];
    printf("reading File:\n");
    read(f,buffer,sizeof(buffer));
    printf("%s\n",buffer);
  }
  else if(strncmp(argv[1], "-r", strlen(argv[1])) == 0){
    struct shmid_ds buf;
    semid = semget(ftok("story.txt",256), 1, 0);
    sc = semctl(semid, 0, IPC_RMID);
    meme = shmget(ftok("control.c",256),66,0);
    sc = semctl(semid,0,IPC_RMID);
    meid = shmctl(meme,IPC_RMID,0);
    printf("Shared mem remove:%d\n",meid);
    printf("semaphore and shared memory removed!%d\n", sc);
    int f = open("story.txt",O_RDONLY);
    char buffer[100000];
    printf("reading File:\n");
    read(f,buffer,sizeof(buffer));
    printf("%s\n",buffer);
  }

  return 0;
}
