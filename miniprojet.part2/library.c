#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.c"
#include "queue.c"

// Add a new book to inventory
void AddNewBook(Inventory* inventory) {
    Book newBook;

    printf("Enter the Book ID: ");
    scanf("%d", &newBook.bookID);
    getchar(); // Clear newline

    printf("Enter the Book Title: ");
    fgets(newBook.title, 50, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0'; // Remove newline

    printf("Enter the Author Name: ");
    fgets(newBook.author, 50, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; // Remove newline

    newBook.isAvailable = true;

    Push(&inventory->head, newBook); // Add to the stack
    printf("Book added successfully!\n");
}

// Borrow a book
void BorrowBook(Inventory* inventory, Queue* requestQueue, UserNode newUser) {
    Stack tempStack;
    InitStack(&tempStack);
    Book tempBook;
    bool found = false;

    // Search for the book in the inventory stack
    while (!isStackEmpty(inventory->head)) {
        Pop(&inventory->head, &tempBook);
        if (tempBook.bookID == newUser.requestedBookID) {
            found = true;
            if (tempBook.isAvailable) {
                tempBook.isAvailable = false;
                printf("The book '%s' has been successfully borrowed. Take care of it!\n", tempBook.title);
            } else {
                printf("The book '%s' is currently unavailable. Adding your request to the queue.\n", tempBook.title);
                Enqueue(requestQueue, newUser);
            }
        }
        Push(&tempStack, tempBook);
    }

    // Restore inventory stack
    while (!isStackEmpty(tempStack)) {
        Pop(&tempStack, &tempBook);
        Push(&inventory->head, tempBook);
    }

    if (!found) {
        printf("Sorry, the book with ID %d is not in our inventory.\n", newUser.requestedBookID);
    }
}

// Return a book
void ReturnBook(Inventory* inventory, int bookID) {
    Stack tempStack;
    InitStack(&tempStack);
    Book tempBook;
    bool found = false;

    // Search for the book in the inventory stack
    while (!isStackEmpty(inventory->head)) {
        Pop(&inventory->head, &tempBook);
        if (tempBook.bookID == bookID) {
            found = true;
            tempBook.isAvailable = true;
            printf("The book '%s' has been successfully returned. Thank you!\n", tempBook.title);
        }
        Push(&tempStack, tempBook);
    }

    // Restore inventory stack
    while (!isStackEmpty(tempStack)) {
        Pop(&tempStack, &tempBook);
        Push(&inventory->head, tempBook);
    }

    if (!found) {
        printf("Sorry, the book with ID %d is not in our inventory.\n", bookID);
    }
}

void ProcessBorrowRequests(Inventory* inventory, Queue* requestQueue) {
    if (isQueueEmpty(*requestQueue)) {
        printf("No pending borrow requests.\n");
        return;
    }

    Queue tempQueue;
    InitQueue(&tempQueue);
    UserNode currentUser;
    Book tempBook;
    Stack tempStack;
    InitStack(&tempStack);

    while (!isQueueEmpty(*requestQueue)) {
        Dequeue(requestQueue, &currentUser);
        bool found = false;

        // Search for the requested book in the inventory stack
        while (!isStackEmpty(inventory->head)) {
            Pop(&inventory->head, &tempBook);
            if (tempBook.bookID == currentUser.requestedBookID) {
                found = true;
                if (tempBook.isAvailable) {
                    tempBook.isAvailable = false;
                    printf("Request for book '%s' processed. User '%s' can now borrow the book.\n",
                           tempBook.title, currentUser.name);
                } else {
                    Enqueue(&tempQueue, currentUser); // Add back to temporary queue
                    printf("The book '%s' is currently unavailable. Request added back to the queue.\n",
                           tempBook.title);
                }
            }
            Push(&tempStack, tempBook);
        }

        // Restore the inventory stack
        while (!isStackEmpty(tempStack)) {
            Pop(&tempStack, &tempBook);
            Push(&inventory->head, tempBook);
        }

        if (!found) {
            printf("Book with ID %d requested by '%s' is not available in the inventory.\n",
                   currentUser.requestedBookID, currentUser.name);
        }
    }

    // Restore remaining requests to the original queue
    while (!isQueueEmpty(tempQueue)) {
        Dequeue(&tempQueue, &currentUser);
        Enqueue(requestQueue, currentUser);
    }
}

void ViewRecentlyReturnedBooks(Stack* recentlyReturned) {
    if (isStackEmpty(*recentlyReturned)) {
        printf("The 'Recently Returned' stack is empty.\n");
        return;
    }

    Stack tempStack;
    InitStack(&tempStack);
    Book tempBook;

    printf("Recently Returned Books:\n");
    printf("------------------------------------\n");

    // Display and temporarily pop books
    while (!isStackEmpty(*recentlyReturned)) {
        Pop(recentlyReturned, &tempBook);
        printf("Book ID: %d\n", tempBook.bookID);
        printf("Title: %s\n", tempBook.title);
        printf("Author: %s\n", tempBook.author);
        printf("------------------------------------\n");
        Push(&tempStack, tempBook); // Restore to the stack later
    }

    // Restore the stack
    while (!isStackEmpty(tempStack)) {
        Pop(&tempStack, &tempBook);
        Push(recentlyReturned, tempBook);
    }
}

void DisplayBorrowRequestQueue(Queue* requestQueue) {
    if (isQueueEmpty(*requestQueue)) {
        printf("The borrow request queue is empty.\n");
        return;
    }

    Queue tempQueue;
    InitQueue(&tempQueue);
    UserNode currentUser;

    printf("Borrow Request Queue:\n");
    printf("-----------------------\n");

    // Display users in the queue temporarily
    while (!isQueueEmpty(*requestQueue)) {
        Dequeue(requestQueue, &currentUser);
        printf("User ID: %d\n", currentUser.userID);
        printf("User Name: %s\n", currentUser.name);
        printf("Requested Book ID: %d\n", currentUser.requestedBookID);
        printf("-----------------------\n");
        Enqueue(&tempQueue, currentUser); // Restore to the queue
    }

    // Restore the queue
    while (!isQueueEmpty(tempQueue)) {
        Dequeue(&tempQueue, &currentUser);
        Enqueue(requestQueue, currentUser);
    }
}

void SearchBook(Inventory* inventory, int bookID) {
    Stack tempStack;
    InitStack(&tempStack);
    Book tempBook;
    bool found = false;

    // Search for the book in the inventory stack
    while (!isStackEmpty(inventory->head)) {
        Pop(&inventory->head, &tempBook);
        if (tempBook.bookID == bookID) {
            printf("Book Found:\n");
            printf("Book ID: %d\n", tempBook.bookID);
            printf("Book Title: %s\n", tempBook.title);
            printf("Author Name: %s\n", tempBook.author);
            printf("Availability: %s\n", tempBook.isAvailable ? "Available" : "Not Available");
            found = true;
        }
        Push(&tempStack, tempBook);
    }

    // Restore inventory stack
    while (!isStackEmpty(tempStack)) {
        Pop(&tempStack, &tempBook);
        Push(&inventory->head, tempBook);
    }

    if (!found) {
        printf("Book with ID %d not found in the inventory.\n", bookID);
    }
}


int main() {
    Inventory inventory = {NULL};
    Queue requestQueue;
    Stack recentlyReturned;

    InitQueue(&requestQueue);
    InitStack(&recentlyReturned);

    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add New Book\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Process Borrow Requests\n");
        printf("5. View Recently Returned Books\n");
        printf("6. Display Borrow Request Queue\n");
        printf("7. Search for a Book\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice) {
            case 1:
                AddNewBook(&inventory);
                break;
            case 2: {
                UserNode newUser;
                printf("Enter User ID: ");
                scanf("%d", &newUser.userID);
                getchar();
                printf("Enter User Name: ");
                fgets(newUser.name, 50, stdin);
                newUser.name[strcspn(newUser.name, "\n")] = '\0';
                printf("Enter Requested Book ID: ");
                scanf("%d", &newUser.requestedBookID);

                BorrowBook(&inventory, &requestQueue, newUser);
                break;
            }
            case 3: {
                int bookID;
                printf("Enter the Book ID to return: ");
                scanf("%d", &bookID);

                ReturnBook(&inventory, bookID);

                // Add the book to the recently returned stack
                Stack tempStack;
                InitStack(&tempStack);
                Book tempBook;
                bool found = false;

                while (!isStackEmpty(inventory.head)) {
                    Pop(&inventory.head, &tempBook);
                    if (tempBook.bookID == bookID) {
                        found = true;
                        Push(&recentlyReturned, tempBook);
                    }
                    Push(&tempStack, tempBook);
                }

                // Restore inventory stack
                while (!isStackEmpty(tempStack)) {
                    Pop(&tempStack, &tempBook);
                    Push(&inventory.head, tempBook);
                }

                if (!found) {
                    printf("Book not found in inventory.\n");
                }
                break;
            }
            case 4:
                ProcessBorrowRequests(&inventory, &requestQueue);
                break;
            case 5:
                ViewRecentlyReturnedBooks(&recentlyReturned);
                break;
            case 6:
                DisplayBorrowRequestQueue(&requestQueue);
                break;
            case 7: {
                int bookID;
                printf("Enter the Book ID to search: ");
                scanf("%d", &bookID);
                SearchBook(&inventory, bookID);
                break;
            }
            case 8:
                printf("Exiting the system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 8);

    return 0;
}
