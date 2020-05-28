/* 
The most important function of the shell is to identify
the commands and ask the OS to perform these.
The parses seperates the commands and identifies them
into various categories
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "shell_util.h"
#include "builtInCommands.h"
#include "execArgs.h"

#define MAX_ARGS_LIST 1024
#define MAX_WORD_LENGTH 1024


//function to parse the commands on the basis of space

void parseSpace(char *line, char **parsed) {
    int i = 0;

    //for every word seperated by space
    //we add it to a 2-D array of words

    for(i = 0; i < MAX_ARGS_LIST; i++) {
        parsed[i] = (char *)malloc(MAX_WORD_LENGTH);
        parsed[i] = strsep(&line, " ");

        if(parsed[i] == NULL) {
            break;
        }

        if(strlen(parsed[i]) == 0) {
            i--;
        }
    }

    return;
}

//This functions does 2 things
//a) identify if any pipe is present
//b) parse the command on the basis of pipes

int parsePipe(char *line, char **pipedLine) {
    int i;

    //for every commands seperated by a pipe
    //commands are added to a 2-D array

    for(i = 0; i < 2; i++) {

        pipedLine[i] = (char *)malloc(MAX_WORD_LENGTH);
        pipedLine[i] = strsep(&line, "|");

        //if no pipe is present break out of the loop
        if(pipedLine[i] == NULL) {
            break;
        }
    }

    //if pipe not found, returns 0
    if(pipedLine[1] == NULL) {
        return 0;
    }

    // if pipe found return 1
    else {
        return 1;
    }

}

//function to classify the entered command
//into builtIn, piped, or any other command

int commandType(char *line, char **parsed, char **parsedPipe) {

    char *strPiped[2];
    int piped = 0;
    piped = parsePipe(line, strPiped);
    if(piped) {

        parseSpace(strPiped[0], parsed);
        parseSpace(strPiped[1], parsedPipe);
    }

    else {
        parseSpace(line, parsed);
    }
    //printf("%d\n", piped);
    /*int i = 0;
    while(parsed[i]) printf("%s\t", parsed[i++]);
    i = 0;*/
    
    if(builtInCommandHandler(parsed)) {
        return 0;
    }
    else {
        return 1 + piped;
    }
    
}

/*int main() {
    char line[MAX_ARGS_LIST], *parsedArgs[MAX_ARGS_LIST], *parsedArgsPiped[MAX_ARGS_LIST];
    fgets(line, MAX_WORD_LENGTH, stdin);
    parseSpace(line, parsedArgs);    
    execArgs(parsedArgs);
    return 0;
}*/
