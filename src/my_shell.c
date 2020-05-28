//This is the driver program
/*/*************************************************************************
 *  ///////////////////////////////////////////////////////////////////  *
 *         Implementation of a Linux Shell in C Programming Language     * 
 *                                                                       *  
 *                  A Project by - Aniket Jayateerth                     * 
 *                          MIS - 111809044                              *
 *  ///////////////////////////////////////////////////////////////////  *
 *                                                                       *
 * ***********************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<wait.h>
#include<readline/readline.h>
#include<readline/history.h>

//Include all the files with function definitions

#include "parser.h"
#include "shell_util.h"
#include "builtInCommands.h"
#include "execArgs.h"
#include "authenticate.h"
#include "color.h"

//maximum word length and arguments length is predefined in the test stage

#define MAX_WORD_LENGTH 1024
#define MAX_ARGS_LENGTH 1024

//main function of the shell
int main(int argc, char** argv)
{
    //initiailisation of the shell

    init_shell();

    char *line, *parsedArgs[MAX_ARGS_LENGTH], *parsedArgsPiped[MAX_ARGS_LENGTH], usr[99];

    int execFlag = 0;
    int mode;

    blue();
    printf("1.Continue to the shell\n\n2.Add a user\n");
    scanf("%d", &mode);
    reset();

    switch(mode) 
    {
        case 1:    
            //The REPL(Read Evaluate Print Loop)

            while(1) 
            {
                line = (char *)malloc(MAX_ARGS_LENGTH);
                
                if(takeInput(line) == 1) 
                {
                    continue;
                }

                //interpret the type of command
                execFlag = commandType(line, parsedArgs, parsedArgsPiped);
                
                //if command is not piped
                if(execFlag == 1) {
                    execArgs(parsedArgs);
                }

                //if command is piped
                if(execFlag == 2) {
                    execArgsPiped(parsedArgs, parsedArgsPiped);
                }
                
            }
            break;

        case 2:
            printf("Add username to add to the database\n");
            scanf("%s", usr);
            if(add_usr(usr))
            puts("User Added");
            break;

        default:
            break;
    }
    return 0;
}
