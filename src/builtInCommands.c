/*

A Utility function to handle built in commands in My_Shell
Since some commands like 'cd' cannot be handled directly by
the OS, it has to be handled by the shell.

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

//A function to handle built in commands

int builtInCommandHandler(char **parsed) 
{
    int noOfCmds = 4, i, switchCommand = 0;
    char *cmds[noOfCmds];

    //List of built in commands that are handled

    cmds[0] = "exit";
    cmds[1] = "cd";
    cmds[2] = "help";
    cmds[3] = "hello";

    //compare the entered command with each of the built in commands

    for(i = 0; i < noOfCmds; i++) 
    {
        //if match is found set switchCommand to i + 1 to indicate which command
        //is to be handled

        if(strcmp(parsed[0], cmds[i]) == 0) 
        {
            switchCommand = i + 1;
            break;
        }
        else
        {
            continue;
        }
    }

    //Switch the variable switchCommand to handle particular cases

    switch(switchCommand) 
    {
        //exit
        case 1:
            puts("\nLogging you out......");
            sleep(1);
            puts("Goodbye!");
            exit(0);

        //cd
        case 2:
            //parsed[1] indicated the path
            chdir(parsed[1]);
            return 1;

        //in built shell-help
        case 3:
            help();
            return 1;

        //in case someone puts hello ;)
        case 4:
            printf("Hello there!\nUse help to know what this shell can do!\n");
            return 1;

        default:
            break;
    }

    return 0;
}

/*int main()
{
    char *ptr[10] = {"cd", "111"};
    builtInCommandHandler(ptr);
    return 0;
}*/
