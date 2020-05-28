typedef struct node {
    char *command;
    struct node *next;
}node;

typedef struct historyStack {
    node *top;
    int noOfNodes;
}historyStack;

void init(historyStack *s);
int isEmpty(historyStack *s);
void push(historyStack *s, char *str);
char* pop(historyStack *s);