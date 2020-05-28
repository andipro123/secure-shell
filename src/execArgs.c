/*
After an entered command is parsed it has to be executed
by the shell. This function is responsible to execute the 
entered commands
There are two functions
1.execArgs can execute all normal UNIX commands 
2.execArgsPiped can execute Piped commands
*/

#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<readline/readline.h> 
#include<readline/history.h> 

#include "execArgs.h"

void execArgs(char **parsed) {

    //Forking a child
    pid_t pid = fork();

    if(pid == -1) {
        fprintf(stderr, "\nFailed Forking a child");
        return;
    }
    
    else if(pid == 0) {
        if(execvp(parsed[0], parsed) < 0) {
            printf("\nCommand not found.");
        }
        exit(0);
    }
    else {
        wait(NULL);
        return;
    }

}


void execArgsPiped(char **parsed, char **parsedPipe) {

    int pipefd[2];
    pid_t p1, p2;

    if(pipe(pipefd) < 0) {

        fprintf(stderr, "Pipe failed to initialize\n");
        return;
    }

    p1 = fork();
    if(p1 < 0) {
        fprintf(stderr, "Failed to fork process\n");
        return;
    }

    if(p1 == 0) {

        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        if(execvp(parsed[0], parsed) < 0) {
            fprintf(stderr, "Failed to execute command 1\n");
            exit(0);
        }
    }
    else {
        p2 = fork();

        if(p2 < 0) {
            fprintf(stderr, "Failed to fork process\n");
            return;
        }

        if(p2 == 0) {

            close(pipefd[1]);

            dup2(pipefd[0], STDIN_FILENO);

            close(pipefd[0]);

            if(execvp(parsedPipe[0], parsedPipe) < 0) {
                fprintf(stderr, "Failed to execute command 2\n");
                exit(0);
            }   
        }
    }
}

/*int main() {
    char *command[10] = {"ls"};
    execArgs(command);
    return 0;
}*/