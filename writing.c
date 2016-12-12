#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main(){
  char comm[512];
  int semid, shmid;
  semid = semget(ftok("story.txt",256),1, 0);
  struct sembuf semcomm;
  semcomm.sem_num = 0;
  semcomm.sem_op = -1;
  semcomm.sem_flg = SEM_UNDO;
  
  semop(semid, &semcomm, 1);
  shmid = shmget(ftok("control.c",256),1000,0);

  int * hold = shmat(shmid,0,0);

  int fd = open("story.txt", O_RDWR|O_APPEND, 0644);
  
  lseek(fd,-1 *(*hold), SEEK_END);
  char buffer[512];
  read(fd,buffer,*hold);
  buffer[*hold]=0;
  printf("Last line:%s\n",buffer);
  
  printf("New Addition:");
  fgets(comm, sizeof(comm), stdin);
  int end = strlen(comm);
  write(fd, comm, end);
  close(fd);
  *hold = strlen(comm);
  shmdt(hold);
  semcomm.sem_op = 1;
  semop(semid, &semcomm,1);
  printf("end\n");
  return 0;
}
