#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"library.h"

void InitQueue(Queue* Q) {
    Q->head = NULL;
    Q->tail = NULL;
}

void Enqueue(Queue* Q, UserNode x) {
    EQueue newNode = malloc(sizeof(QNode));
    newNode->data = x;
    newNode->next = NULL;
    if (Q->head == NULL) {
        Q->head = newNode;
    } else {
        Q->tail->next = newNode;
    }
    Q->tail = newNode;
}

void Dequeue(Queue* Q, UserNode* x) {
    if (Q->head == NULL) return; // Queue is empty
    EQueue temp = Q->head;
    *x = temp->data;
    Q->head = Q->head->next;
    if (Q->head == NULL) {
        Q->tail = NULL;
    }
    free(temp);
}

bool isQueueEmpty(Queue Q) {
    return (Q.head == NULL);
}
