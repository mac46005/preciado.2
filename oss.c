//AUTHOR: Marco Preciado
//DESCRIPTION:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <time.h>


#define SHMKEY 466600
#define BUFF_SZ sizeof(int)

int proc;
int simul;
int timeLimit;




struct PCB{
    int occupied;
    pid_t pid;
    int startSeconds;
    int startNano;
};

struct PCB processTable[20];




int main(int argc, char* argv[]){
    if(processGetOpt(argc, argv) == 0){

    }else{
        helpMessage();
        exit 1;
    }
}

int processGetOpt(int argc, char* argv[]){
    const char* options = "hn:s:t:";
    char opt;
    int exit = 1;

    while((opt = getopt(argc, argv, options))){
        switch(opt){
            case 'h':
                helpMessage();
                exit 1;
                break;
            case 'n':
                if(digits_only(optarg) == 0){
                    proc = atoi(optarg);
                    exit 0;
                }else{
                    fprintf(stderr, "");
                    exit = 1;
                }
                break;
            case 's':
                if(digits_only(optarg) == 0){
                    simul = atoi(optarg);
                    exit = 0;
                }else{
                    fprintf(stderr, "");
                    exit = 1;
                }
                break;
            case 't':
                if(digits_only(optarg) == 0){
                    timeLimit = atoi(optarg);
                    exit = 0;
                }else{
                    fprintf(stderr, "");
                    exit = 1;
                }
                break;
        }

        return exit;
    }

    return 0;
}


void child(){

}




void parent(){

}

void exitMessage(){
    printf("Goodbye!");
}
void helpMessage(){
    printf("Welcome to timed workers program\n");
    printf("DESCRIPTION:")
    printf("Please input a positive integer for the following options\n");
    printf("-n arg, where arg is the number of workers to launch\n")
    printf("-s arg, where arg is the number of workers that lauch synchronously\n");
    printf("-t arg, where arg is the alloted time a worker will hang around\n");
    printf("\n\nEXAMPLE:\n./oss -n 3 -s 2 -t 4\nThe following example above will produce 3 workers\nof which 2 of the workers will work in synchronous\nand will assign a time between 1 and 4 seconds for a worker to hang around\n");
}

void optargError(char* message, char* value){
    fprintf(stderr, "ERROR: %s\n INPUT VALUE:%s\n", message, value);
}

int digits_only(const char* string){
    while(*s){
        if(isdigit(*s++) == 0){
            return 0;
        }
    }
    return 1;
}