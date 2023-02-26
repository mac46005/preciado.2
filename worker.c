#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shrdmem.h"
int main(int argc, char* argv[]){
    int secondsStay, nanoStay;
    int shmid = shmget(SHMKEY_1, BUff_SZ, 0777);
    if(shmid == -1){
        fprintf(stderr, "Child:...Error in shmget...");
        return 1;
    }

    int* cint = (int*)(shmat(shmid, 0, 0));
    printf("seconds from shrdmem %d\n", cint[0]);
    printf("nanoseconds from shrdmem %d\n", cint[1]);
    // secondsStay = atoi(argv[1]);
    // nanoStay = atoi(argv[2]);
    printf("Child about to sleep\n");
    sleep(2);
    printf("Child done\n");
    return 0;
}