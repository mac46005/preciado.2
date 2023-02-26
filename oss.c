//FILE: oss.c
//AUTHOR: Marco Preciado
//DESCRIPTION: 





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include "igetopt_helper.h"
#include "ioss.h"
#include "shrdmem.h"

struct PCB{
    int occupied;
    pid_t pid;
    int start_seconds;
    int start_nano;
};
// int shmid1 = shmget(SHMKEY_1, BUff_SZ, 0777 | IPC_CREAT);
//         printf("key :%d\n" ,shmid1);
//         if(shmid1 == -1){
//             fprintf(stderr, "Error in shmget\n");
//         }
//         int* paddr = (int*)(shmat(shmid1, 0,0));
//         shmdt(paddr);
//         shmctl(shmid1, IPC_RMID, NULL);
struct PCB process_table[20];

int main(int argc, char* argv[]){
    pid_t pid;
    int count = 0;
    int status;
    pid_t terminated_child;
    pid_t simul_pid[simul];
    int a_child_terminated = 0;
    if(process_getopt(argc, argv) == 0){
        while(proc != 0){
            increment_clock();
            int shdm_id = shmget(SHMKEY_1, BUff_SZ, 0777 | IPC_CREAT);
            int* paddr = (int*)(shmat(shdm_id, 0, 0));
            paddr[0] = seconds;
            paddr[1] = nanoseconds;




            if(simul != 0){
                pid = fork();
                if(pid == 0){
                    child();
                }
                    struct PCB new_child;
                    new_child.occupied = 1;
                    printf("child pid %d\n", pid);
                    sleep(1);
                    new_child.pid = pid;
                    new_child.start_seconds = seconds;
                    new_child.start_nano = nanoseconds;
                    process_table[count] = new_child;
                    simul_pid[count] = pid;
                    count++;
                    proc--;
                
            }

            int i;
            for(i = 0; i <= count; i++){
                if((terminated_child = waitpid(simul_pid[count],&status, WNOHANG)) == 0){
                    a_child_terminated = 0;
                    terminated_child = simul_pid[count];
                    print_process_table();
                }
            }
            if(a_child_terminated == 0){
                printf("a child terminated: %d\n", terminated_child);
                for(i = 0;i < count; i++){
                    if(process_table[i].pid = terminated_child){
                        process_table[i].occupied = 0;
                        print_process_table();
                    }
                }
                if(simul == 0){
                    pid = fork();
                    if(pid == 0){
                        child();
                    }else{
                        struct PCB new_child;
                        new_child.occupied = 1;
                        new_child.pid = pid;
                        new_child.start_seconds = seconds;
                        new_child.start_nano = nanoseconds;
                        count++;
                        wait(&status);
                    }
                }
            }
        }
    }else{
        help_message();
        exit(1);
    }
    exit(0);
}









//igetopt_helper.h/////////////////////////////
int process_getopt(int argc, char* argv[]){
    const char* options = "hn:s:t:";
    char val[200];
    char opt;
    int exit = 1;
    while((opt = getopt(argc, argv, options)) != -1){
        switch(opt){
            case 'h':
                help_message();
                exit = 1;
                break;
            case 'n':
                if(digits_only(optarg) == 0){
                    proc = atoi(optarg);
                    exit = 0;
                }else{
                    option_err(opt, optarg);
                }
                break;
            case 's':
                if(digits_only(optarg) == 0){
                    simul = atoi(optarg);
                    exit = 0;
                }else{
                    option_err(opt, optarg);
                }
                break;
            case 't':
                if(digits_only(optarg) == 0){
                    time_limit = atoi(optarg);
                    exit = 0;
                }else{
                    option_err(opt, optarg);
                }
                break;
            default:
                help_message();
                exit = 1;
                break;
        }
    }
    return exit;
}
void option_err(char opt, char* value){
    fprintf(stderr, "ERROR: option %c has invalid value %s\n", opt, value);
}
void exit_message(){
    printf("Thank you for utilizing oss. Exiting...n");
}
void help_message(){
    printf("Welcome to timed workers program\n");
    printf("DESCRIPTION:");
    printf("Please input a positive integer for the following options\n");
    printf("-n arg, where arg is the number of workers to launch\n");
    printf("-s arg, where arg is the number of workers that lauch synchronously\n");
    printf("-t arg, where arg is the alloted time a worker will hang around\n");
    printf("\n\nEXAMPLE:\n./oss -n 3 -s 2 -t 4\nThe following example above will produce 3 workers\nof which 2 of the workers will work in synchronous\nand will assign a time between 1 and 4 seconds for a worker to hang around\n");
}
int digits_only(const char* string){
    int exit = 1;
    int i;
    int length = strlen(string);
    for(i = 0; i < length; i++){
        if(string[i] >= '0' && string[i] <= '9'){
            exit = 0;
        }else{
            exit = 1;
        }
    }
    return exit;
}
///END/////////////////////////////////////////
///ioss.h//////////////////////////////////////
void child(){
    char* prgnm = "./worker";
    char sec_str[12];
    char nano_str[12];
    sprintf(sec_str, "%d", seconds);
    sprintf(nano_str, "%d", nanoseconds);
    char* args[] = {prgnm, sec_str, nano_str, NULL};
    execv(prgnm, args);
}
void parent(pid_t child, int process_num){
    struct PCB childBlock;
    childBlock.pid = child;
    childBlock.start_seconds = seconds;
    childBlock.start_nano = nanoseconds;
    childBlock.occupied = process_num;
}
void check_if_child_has_terminated(){
    int status;
    int pid = waitpid(-1, &status, WNOHANG);
}
void print_process_table(){
    printf("OSS PID: %d SysClockS: %d SysclockNano: %d\n", getpid(), seconds, nanoseconds);
    printf("Process Table:\n");
    printf("Entry\tOccupied\tPID\tStarts\tStartN\n");
    int i;
    for(i = 0; i < 20; i++){
        printf("%d\t%d\t\t%d\t%d\t%d\n",i,process_table[i].occupied,process_table[i].pid,process_table[i].start_seconds,process_table[i].start_nano);
    }
}
void increment_clock(){
    if(nanoseconds > 999999999){
        seconds++;
        nanoseconds = 0;
    }else{
        nanoseconds += 10000;
    }
}
///END/////////////////////////////////////////
