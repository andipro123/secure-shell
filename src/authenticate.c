/*
This program is a utility program to authenticate whether
the user has access to the terminal. It uses simple Caesar Cipher algorithm
to encrpyt or decrypt a string.

The main functions of the program are:
1. To authenticate whether the entered user is a registered user
2. Register a new user
3. Encrypt and decrypt usernames and store/extract them from a file

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

#define MAX_WORD_LENGTH 1024

//Function to encrpyt a string using Caesar Cipher Algorithm

char *encryptString(char *str) 
{
    int i, x;
    char *arr = (char *)malloc(strlen(str) + 1);

    //random key to alter the string

    x = 5;

    for(i = 0; i < strlen(str); i++) 
    {
        // Every letter in the string is altered to
        // generate a code

        arr[i] = str[i] + x;
    }
    arr[i] = '\0';

    return arr;
}


// Function to decrpyt the entered string
// it returns the decrpyted string

char *decryptString(char *str) 
{
    int i, x;
    char *arr = (char *)malloc(strlen(str) + 1);
    x = 5;

    for(i = 0; i < strlen(str); i++) 
    {
        // Every letter in the string is altered to
        // decipher the code

        arr[i] = str[i] - x;
    }
    arr[i] = '\0';

    return arr;
}

//Function to add a new user to the existing user data_base
//Requires you to be signed in

int add_usr(char *usr) {

    //open usernames file
    FILE *fp = fopen("usr_names", "a");
    if(!fp)
    {
        fprintf(stderr, "Unable to fetch database\n");
        exit(1);
    }

    //add encrypted name to the file
    fprintf(fp, "%s\n", encryptString(usr));
    fclose(fp);
    return 1;
}

// Function to authenticate whether an user is a registered user
// A special file consisting of various codes is present
// This function verifies whether given user matches with any encoded user

int authenticate(char *code) 
{
    //open usernames file

    FILE *fp = fopen("usr_names", "r");
    if(!fp)
    {
        fprintf(stderr, "Unable to authenticate!\nFatal Error\n");
        exit(1);
    }

    char name[MAX_WORD_LENGTH];
    int flag = 0;

    while(!feof(fp)) 
    {
        fscanf(fp, "%s", name);
        //Compare entered string with deciphered values from the file

        if(strcmp(code, decryptString(name)) == 0) 
        {
            flag = 1;
            break;
        }
        else
        {
            continue;
        }
    }

    fclose(fp);
    // If a match is found function returns 1

    if(flag == 1) 
    {
        return 1;
    }

    // If a match is not found function returns 0

    else
    {
        return 0;
    }
}

/*int main() 
{
    int x = authenticate("teacher");
    if(x == 1) puts("yes");
    else puts("no");
    return 0;
}*/