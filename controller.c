#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define KEY 33333

void create_s(int n) {
  int sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0777);  
  if (sd == -1) {
    printf("The semaphore already exists!\n");
  }
  else {
    semctl(sd, 0, SETVAL, n);
    printf("Semaphore %d created with value: %d\n", sd, n);
  }
}

void view_s() {
  int sd = semget(KEY, 0, 0777);
  if (sd == -1) {
    printf("Error! Unable to retrieve value.\n");
  }
  else {
    int value = semctl(sd, 0, GETVAL);
    printf("Semaphore %d has value: %d.\n", sd, value);
  }
}

void remove_s() {
  int sd = semget(KEY, 1, 0777);
  if (sd == -1) {
    printf("Error! Unable to remove semaphore.\n");
  }
  else {
    if (semctl(sd, 0, IPC_RMID)) {
      printf("Unable to remove semaphore!\n");
    }
    else {
      printf("Semaphore %d removed!\n", sd);
    }
  }
}

int main(int argc, char *argv[]) {
  if (!strcmp(argv[1], "-c")) {
    create_s(atoi(argv[2]));
  }
  else if (!strcmp(argv[1], "-v")) {
    view_s();
  }
  else if (!strcmp(argv[1], "-r")) {
    remove_s();
  }
  return 0;
}