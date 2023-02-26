#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shrdmem.h"

int main(int argc, char* argv[]){





    printf("seconds given: %s                ", argv[1]);
    printf("nano given: %s\n", argv[2]);



    int secondsStay, nanoStay;
    int shmid = shmget(SHMKEY_1, BUff_SZ, 0777);
    
    if(shmid == -1){
        fprintf(stderr, "Child:...Error in shmget...\n");
        return 1;
    }

    int* cint = (int*)(shmat(shmid, 0, 0));
    printf("seconds from shrdmem %d\n", cint[0]);
    printf("nanoseconds from shrdmem %d\n", cint[1]);
    
    // secondsStay = atoi(argv[1]);
    // nanoStay = atoi(argv[2]);
    printf("Child about to sleep\n");
    sleep(7);
    printf("Child done\n");
    shmdt(cint);
    return 0;
}