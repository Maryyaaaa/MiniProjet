#pragma once

typedef struct UserNode {
    int userID;
    char name[50];
    int requestedBookID;
    struct UserNode* next; // Pointer to the next user (queue)
} UserNode;

// Book structure
typedef struct Book {
    int bookID;
    char title[50];
    char author[50];
    bool isAvailable;
    struct Book* next; // Pointer to the next book
} Book;

typedef struct Estack* Stack;

typedef struct Estack {
    Book data;   // Book data for the stack
    Stack next;  // Pointer to the next element in the stack
} SNode;

// Inventory structure as a stack
typedef struct {
    Stack head; // Pointer to the top of the stack
} Inventory;

typedef struct Element* EQueue;

typedef struct Element {
    UserNode data; // UserNode data for the queue
    EQueue next;   // Pointer to the next element in the queue
} QNode;

typedef struct {
    EQueue head, tail; // Head and tail pointers for the queue
} Queue;

void AddNewBook(Inventory* inventory);
void BorrowBook(Inventory* inventory, Queue* requestQueue, UserNode newUser);
void ReturnBook(Inventory* inventory, int bookID);
void ProcessBorrowRequests(Inventory* inventory, Queue* requestQueue);
void ViewRecentlyReturnedBooks(Stack* recentlyReturned);
void DisplayBorrowRequestQueue(Queue* requestQueue);
void SearchBook(Inventory* inventory, int bookID);
void InitStack(Stack* S);
void Push(Stack* S, Book x);
void Pop(Stack* S, Book* x);
bool isStackEmpty(Stack S);
void InitQueue(Queue* Q);
void Enqueue(Queue* Q, UserNode x);
void Dequeue(Queue* Q, UserNode* x);
bool isQueueEmpty(Queue Q);
