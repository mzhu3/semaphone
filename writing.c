#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
struct sembuf {
  ushort  sem_num;        /* semaphore index in array */
  short   sem_op;         /* semaphore operation */
  short   sem_flg;        /* operation flags */
};
int main(){
  char comm[512];
  int sem, shm;
  sem = semget(ftok("story.txt",256),1, IPC_CREAT| 0644);
  shm = shmget(24333, sizeof(char), IPC_CREAT | 0644);
  struct sembuf *semcomm = {0, -1, SEM_UNDO};
  /*
  semcomm.sem_num = 0;
  semcomm.sem_op = -1;
  semcomm.sem_flg = SEM_UNDO;
  */
  semop(sem, semcomm, 1);
  int fd = open("story.txt", O_RDWR|O_APPEND, 0644);
  char line;
  line = shmat(shm, line, 0);
  printf("Previous line: \"%c\"\n", line);
  fgets(comm, sizeof(comm), stdin);
  write(fd, comm, 1024);
  shmat(shm, comm, 0);
  return 0;
}