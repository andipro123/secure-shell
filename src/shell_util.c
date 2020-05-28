/*
Various small functions can be grouped together
as they all are involved in making the accessories of the
shell
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


//function definition to clear the terminal
#define clear() printf("\033[H\033[J")

#define BUFFER 1024

#include "authenticate.h"
#include "color.h"

//Function to initialise the shell and start the shell in the existing terminal window

int init_shell() 
{
    clear();

    char usr_name[20];

    red();

    printf("********************************************************************************************\n");
    printf("****************************************MY_SHELL********************************************\n");
    printf("********************************************************************************************\n\n");

    cyan();
    printf("Enter user_name to continue\n");
    scanf("%s", usr_name);

    //authenticate whether user has access to the shell or not
    int x = authenticate(usr_name);

    //if verified shell starts
    if(x) 
    {
        clear();

        green();
        printf("Authentication Successful\n");
        reset();
        return 0;
    }

    //if authentication fails the program is terminated
    else 
    {
        clear();

        red();
        printf("Authentication error\n");
        reset();
        exit(1);
    }
}

// function to add entered commands to a seperate file
int add_to_history(char *str) 
{
    int fd = open("history", O_APPEND|O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
    if(fd == -1) 
    {
       printf("Unable to locate terminal history\n");
       return 0;
    }
    write(fd, str, strlen(str));
    write(fd, "\n", 1);
    return 0;
}


//function to print the current directory boefore every commands is entered

void printDir() 
{
    char dir[BUFFER];
    getcwd(dir, sizeof(dir));
    blue();
    printf("~%s ", dir);
    reset();
}

//function to take commands from the user in the terminals
int takeInput(char *str) 
{
    char *line;

    yellow();
    printf("You are using MY_SHELL");
    reset();

    //print current directory
    printDir();

 
    line = readline(" $>> ");
    
    if(strlen(line) != 0)
    {
        add_to_history(line);
        add_history(line);
        strcpy(str, line);
        return 0;
    }
    else 
    {
        return 1;
    }
}

//utility function to print help for the shell
//it prints the various functions this shell can perform

void help() 
{
    puts("\n****Welcome to My_Shell Help****"
    "\n****DSA_PROJECT****"
    "\n\nList of commands supported:"
    "\n1. cd"
    "\n2. ls"
    "\n3. exit"
    "\n4. Basic UNIX commands\n"
    "5. Piped Commands");
    return;
}

/*int main() {
    char st[10];
    if(init_shell() == 1){
        exit(1);
    }
    printDir();
    help();
    return 0;
}*/
