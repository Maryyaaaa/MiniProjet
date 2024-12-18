#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"library.h"

void InitStack(Stack* S) {
    *S = NULL;
}

void Push(Stack* S, Book x) {
    Stack newNode = malloc(sizeof(SNode));
    newNode->data = x;
    newNode->next = *S;
    *S = newNode;
}

void Pop(Stack* S, Book* x) {
    if (*S == NULL) return; // Stack is empty
    Stack temp = *S;
    *x = temp->data;
    *S = temp->next;
    free(temp);
}

bool isStackEmpty(Stack S) {
    return (S == NULL);
}
