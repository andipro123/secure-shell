/*
a stack of char pointers used to maintain history
in the shell
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "historyStack.h"
/*typedef struct node {
    char *command;
    struct node *next;
}node;

typedef struct historyStack {
    node *top;
    int noOfNodes;
}historyStack;*/

void init(historyStack *s) 
{
    s -> top = NULL;
    s -> noOfNodes = 0;
}

int isEmpty(historyStack *s) 
{
    return s -> noOfNodes == 0;
}

void push(historyStack *s, char *str) 
{
    node *ptr = (node *)malloc(sizeof(node));
    s -> noOfNodes++;
    ptr -> next = s -> top;
    ptr -> command = (char *)malloc(strlen(str) + 1);
    strcpy(ptr -> command, str);
    s -> top = ptr;
}

char* pop(historyStack *s) 
{
    if(isEmpty(s))
        return "";
    node *ptr = s -> top;
    char *str = ptr -> command;
    s -> top = ptr -> next;
    free(ptr);
    s -> noOfNodes--;
    return str;
}