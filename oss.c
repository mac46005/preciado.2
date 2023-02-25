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

struct PCB process_table[20];

int main(int argc, char* argv[]){
    pid_t pid;
    int count = 0;

    if(process_getopt(argc, argv) == 0){

        while(seconds != 5){
            increment_clock();
            if(nanoseconds == 500000000){
                print_process_table();
            }
            usleep(1);
            // int status;
            // waitpid(pid, &status, 0);
            // if(WIFEXITED(status)){
            //     if(pid != NULL){
            //         process_table[count].occupied = 0;
            //     }
            //     count++;
            //     pid = fork();
            //     if(pid == 0){
            //         char* prgnm = "./worker";
            //         char sec_str[12];
            //         char nano_str[12];
            //         sprintf(sec_str, "%d", seconds);
            //         sprintf(nano_str, "%d", nanoseconds);
            //         char* args[] = {prgnm, sec_str, nano_str,NULL};
            //         execv(prgnm, args);

            //     }else{
            //         struct PCB new_p;
            //         new_p.pid = pid;
            //         new_p.start_nano = seconds;
            //         new_p.start_seconds = nanoseconds;
            //         new_p.occupied = count;
            //     }
            // }
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
    exit(0);
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
