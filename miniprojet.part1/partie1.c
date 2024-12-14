#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Task {
    int id;
    char description[100];
    int priority; // Priority level (1-5)
    char status[20]; // "Pending", "In Progress", "Completed"
    struct Task *next;
} Task;

// Function prototypes
Task* insertTask(Task* head, int id, const char* description, int priority, const char* status);
Task* deleteTask(Task* head, int id);
Task* updateStatus(Task* head, int id, const char* newStatus);
void displayTasks(Task* head);
void searchByPriority(Task* head, int priority);

// Insert a task in order of priority
Task* insertTask(Task* head, int id, const char* description, int priority, const char* status) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->priority = priority;                   
    strcpy(newTask->status, status);
    newTask->next = NULL;

    if (head == NULL || head->priority < priority) {
        newTask->next = head;
        printf("Task successfully added.\n");
        return newTask;
    }

    Task* current = head;
    while (current->next != NULL && current->next->priority >= priority) {
        current = current->next;
    }
    newTask->next = current->next;
    current->next = newTask;
    printf("Task successfully added.\n");
    return head;
}

// Delete a task by its ID
Task* deleteTask(Task* head, int id) {
    if (head == NULL) {
        printf("Task list is empty.\n");
        return head;
    }

    if (head->id == id) {
        Task* temp = head;
        head = head->next;
        free(temp);
        printf("Task with ID %d successfully deleted.\n", id);
        return head;
    }

    Task* current = head;
    while (current->next != NULL && current->next->id != id) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Task with ID %d not found.\n", id);
    } else {
        Task* temp = current->next;
        current->next = temp->next;
        free(temp);
        printf("Task with ID %d successfully deleted.\n", id);
    }

    return head;
}

// Update the status of a task by its ID
Task* updateStatus(Task* head, int id, const char* newStatus) {
    Task* current = head;
    while (current != NULL) {
        if (current->id == id) {
            if (strcmp(newStatus, "Pending") == 0 || strcmp(newStatus, "In Progress") == 0 || strcmp(newStatus, "Completed") == 0 ||strcmp(newStatus, "pending") == 0 || strcmp(newStatus, "in progress") == 0 || strcmp(newStatus, "completed") == 0) {
                strcpy(current->status, newStatus);
                printf("Task ID %d status successfully updated to '%s'.\n", id, newStatus);
            } else {
                printf("Invalid status. Use 'Pending', 'In Progress', or 'Completed'.\n");
            }
            return head;
        }
        current = current->next;
    }

    printf("Task with ID %d not found.\n", id);
    return head;
}

// Display tasks grouped by their current status
void displayTasks(Task* head) {
    if (head == NULL) {
        printf("No tasks have been inserted yet!\n");
        return;
    }

    printf("\nPending Tasks:\n");
    Task* current = head;
    while (current != NULL) {
        if (strcmp(current->status, "Pending") == 0||strcmp(current->status, "pending") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", current->id, current->description, current->priority);
        }
        current = current->next;
    }

    printf("\nIn Progress Tasks:\n");
    current = head;
    while (current != NULL) {
        if (strcmp(current->status, "In Progress") == 0 ||strcmp(current->status, "in progress") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", current->id, current->description, current->priority);
        }
        current = current->next;
    }

    printf("\nCompleted Tasks:\n");
    current = head;
    while (current != NULL) {
        if (strcmp(current->status, "Completed") == 0 || strcmp(current->status, "completed") == 0) {
            printf("ID: %d, Description: %s, Priority: %d\n", current->id, current->description, current->priority);
        }
        current = current->next;
    }
}

// Search and display tasks by priority
void searchByPriority(Task* head, int priority) {
    Task* current = head;
    bool found = false;
    printf("\nTasks with Priority %d:\n", priority);
    while (current != NULL) {
        if (current->priority == priority) {
            printf("ID: %d, Description: %s, Status: %s\n", current->id, current->description, current->status);
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        printf("No tasks with priority %d found.\n", priority);
    }
}

int main() {
    int enter;
    Task* taskList = NULL;
    int ID, priority;
    char description[100], status[20], NewStatus[20];

    printf("Welcome To The Task Management System!\n");
    do {
        printf("Click on 0 to enter the Menu.\n");
        scanf("%d", &enter);
    } while (enter != 0);

    while (enter == 0) {
        printf("The Menu:\n");
        printf("1. Task Insertion\n2. Task Deletion\n3. Update Status\n4. Display Tasks\n5. Search by Priority\n");
        printf("\nEnter which operation you want to execute: ");

        scanf("%d", &enter);
        if (enter == 1) {
            printf("Enter the ID of the task: ");
            scanf("%d", &ID);
            getchar(); // Clear newline character from buffer
            printf("Provide the description: ");
            fgets(description, 100, stdin);
            description[strcspn(description, "\n")] = 0; // Remove newline      
            do
            {
              printf("Enter the priority level (1-5): ");
              scanf("%d", &priority);
            } while (priority <1 || priority>5);
            
            getchar(); // Clear newline character from buffer
            printf("Insert the status of your task (Pending , In Progress , Completed): ");
            fgets(status, 20, stdin);
            status[strcspn(status, "\n")] = 0; // Remove newline
            taskList = insertTask(taskList, ID, description, priority, status);
        }

        if (enter == 2) {
            printf("Enter the ID of the task you want to delete: ");
            scanf("%d", &ID);
            taskList = deleteTask(taskList, ID);
        }

        if (enter == 3) {
            printf("Enter the ID of the task you want to update: ");
            scanf("%d", &ID);
            getchar(); // Clear newline character from buffer
            printf("Enter the new status: ");
            fgets(NewStatus, 20, stdin);
            NewStatus[strcspn(NewStatus, "\n")] = 0; // Remove newline
            taskList = updateStatus(taskList, ID, NewStatus);
        }

        if (enter == 4) {
            displayTasks(taskList);
        }

        if (enter == 5) {
            printf("Provide the priority of the task you're searching for: ");
            scanf("%d", &priority);
            searchByPriority(taskList, priority);
        }
        printf("\nEnter 0 to go back to the Menu \n");
        scanf("%d", &enter);
    }
    return 0;
}
