//AUTHOR: Marco Preciado
//DESCRIPTION:


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int seconds = 0;
extern int nano = 0;

struct PCB{
    int occupied;
    pid_t pid;
    int startSeconds;
    int startNano;
};

int main(int argc, char* argv[]){

}

void incrementClock(){
    if(nano >= 99999999){
        nano = 0;
        seconds++;
    }else{
        nano += 111111;
    }
}
