#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include<sys/wait.h> 

int main(){
    int child1, child2;
    child1 = fork();
    if(child1 == 0) { 
        //This is child 1
        printf("I am a child. My pid is: %d\n", getpid());
        srand(time(NULL) + getpid());
        int sleeptimer = rand() % 9 + 2;
        sleep(sleeptimer);
        printf("CHILD: I have awoken. My pid is: %d, and I slept for %d seconds.\n", getpid(), sleeptimer);
        return sleeptimer;
    } else if(child1 > 0) { //Parent creates another child here
        child2 = fork();
        if(child2 == 0){ 
            //This is child 2
            printf("I am a child. My pid is: %d\n", getpid());
            srand(time(NULL) + getpid());
            int sleeptimer = rand() % 9 + 2;
            sleep(sleeptimer);
            printf("I am a child and I have AWOKEN. My pid is: %d, and I slept for %d seconds.\n", getpid(), sleeptimer);
            return sleeptimer;
        } else if(child2 > 0){ 
            //This is the parent
            int status_code;
            int child_pid = wait(&status_code);
            printf("Parent here. Child with: %d, slept for %d seconds.\n", child_pid, WEXITSTATUS(status_code)); 
            printf("Parent here. I'm finished.\n");
            return 0;
        }
        return -1;
    }
    return -1;
}