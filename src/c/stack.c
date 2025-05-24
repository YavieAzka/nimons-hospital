#include "../header/stack.h"

void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack s) {
    return s.top == -1;
}

int isStackFull(Stack s) {
    return s.top == MAX_STACK - 1;
}

void push(Stack* s, int value) {
    if (!isStackFull(*s)) {
        s->data[++s->top] = value;
    }
}

int pop(Stack* s) {
    if (!isStackEmpty(*s)) {
        return s->data[s->top--];
    }
    return -1; 
}

int peek(Stack s) {
    if (!isStackEmpty(s)) {
        return s.data[s.top];
    }
    return -1;
}
