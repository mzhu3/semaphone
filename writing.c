#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
int main(){
  char comm[512];
  int semid, shmid;
  semid = semget(ftok("story.txt",256),1, 0);
  struct sembuf semcomm;
  semcomm.sem_num = 0;
  semcomm.sem_op = -1;
  semcomm.sem_flg = SEM_UNDO;
  
  semop(semid, &semcomm, 1);
  shmid = shmget(ftok("control.c",256),66,0);

  int * hold = shmat(shmid,0,0);
  char *buffer;
  int fd = open("story.txt", O_RDWR|O_APPEND, 0644);
  
  lseek(fd,-1 *(*hold),SEEK_END);
  read(fd,buffer,*hold);
  printf("Last line:%s\n",buffer);
  printf("New Addition:");
  fgets(comm, sizeof(comm), stdin);
  int end = strlen(comm)+2;
  write(fd, comm, end);
  close(fd);
  shmdt(hold);
  semcomm.sem_op = 1;
  semop(semid, &semcomm,1);
  printf("end\n");
  return 0;
}
