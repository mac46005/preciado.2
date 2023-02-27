#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include "shrdmem.h"

void print_worker(int sys_sec, int sys_nano){
    printf("WORKER PID:%d PPID:%d SysclockS:%d SysclockNano:%d\n", getpid(), getppid(), sys_sec, sys_nano);
}

int get_sec_stay_time(int given_sec,int start_sec){
    return start_sec + given_sec;
}

int get_nano_stay_time(int given_nano,int start_nano){
    if(start_nano > 999999999){
        return given_nano;
    }
    return start_nano + given_nano;
}


int main(int argc, char* argv[]){





    


    int given_sec, given_nano;
    int shmid = shmget(SHMKEY, BUff_SZ, 0666);

    if(shmid == -1){
        fprintf(stderr, "Child:...Error in shmget...\n");
        return 1;
    }
    int* shared_mem_address = (int*)(shmat(shmid, NULL, 0));


    given_sec = atoi(argv[1]);
    given_nano = atoi(argv[2]);
    

    print_worker(shared_mem_address[0], shared_mem_address[1]);
    int sec_stay = get_sec_stay_time(given_sec, shared_mem_address[0]);
    int nano_stay = get_nano_stay_time(given_nano, shared_mem_address[1]);

    printf("pid: %d sec_stay:%d\n", getpid(),sec_stay);
    printf("pid: %d nano_stay:%d\n",getpid(),nano_stay);

    int count = 0;
    printf("about to loop worker till time\n");
    while(sec_stay > shared_mem_address[0] && nano_stay > shared_mem_address[1]){
            printf("%d %d:%d\n",getpid(), shared_mem_address[0], shared_mem_address[1]);
    }

    print_worker(shared_mem_address[0], shared_mem_address[1]);
    printf("--Terminating\n");

    shmdt(shared_mem_address);
    return 0;
}