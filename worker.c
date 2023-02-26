#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shrdmem.h"

void print_worker(int sys_sec, int sys_nano){
    printf("WORKER PID:%d PPID:%d SysclockS:%d SysclockNano:%d\n", getpid(), getppid(), sys_sec, sys_nano);
}

int main(int argc, char* argv[]){





    


    int secondsStay, nanoStay;
    int shmid = shmget(SHMKEY, BUff_SZ, 0666);

    if(shmid == -1){
        fprintf(stderr, "Child:...Error in shmget...\n");
        return 1;
    }
    int* cint = (int*)(shmat(shmid, NULL, 0));


    secondsStay = atoi(argv[1]);
    nanoStay = atoi(argv[2]);
    printf("Given rand sec: %d nano: %d\n", secondsStay, nanoStay);
    print_worker(cint[0], cint[1]);

    sleep(10);


    shmdt(cint);
    return 0;
}