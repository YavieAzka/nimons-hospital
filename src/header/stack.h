#ifndef STACK_H
#define STACK_H

#define MAX_STACK 100

typedef struct {
    int data[MAX_STACK]; 
    int top;
} Stack;

void initStack(Stack* s);
int isStackEmpty(Stack s);
int isStackFull(Stack s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack s);

#endif
