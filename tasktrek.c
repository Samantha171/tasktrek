#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TASKS 100
#define FILENAME "tasks"

typedef struct {
    char name[50];
    int priority;
} Task;

typedef struct {
    Task tasks[MAX_TASKS];
    int size;
} PriorityQueue;

void initialize(PriorityQueue *pq);
void swap(Task *a, Task *b);
void insert(PriorityQueue *pq, Task task);
Task removeHighestPriority(PriorityQueue *pq);
void displayMenu();
void clearInputBuffer();
void addTask(PriorityQueue *pq);
void executeTask(PriorityQueue *pq);
void displayAllTasks(PriorityQueue *pq);
void saveTasksToFile(PriorityQueue *pq);
void loadTasksFromFile(PriorityQueue *pq);

void initialize(PriorityQueue *pq) {
    pq->size = 0;
}

void swap(Task *a, Task *b) {
    Task temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue *pq, Task task) {
    if (pq->size == MAX_TASKS) {
        printf("Error: Priority queue is full!\n");
        return;
    }
    int i = pq->size;
    if (task.priority == 1) {
        memmove(&pq->tasks[1], &pq->tasks[0], pq->size * sizeof(Task));
        pq->tasks[0] = task;
    } else {
        pq->tasks[pq->size] = task;
        while (i > 0 && pq->tasks[(i - 1) / 2].priority < pq->tasks[i].priority) {
            swap(&pq->tasks[(i - 1) / 2], &pq->tasks[i]);
            i = (i - 1) / 2;
        }
    }
    pq->size++;
    printf("Task added successfully.\n");
}

Task removeHighestPriority(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Error: Priority queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < pq->size; i++) {
        if (pq->tasks[i].priority == 1) {
            Task task = pq->tasks[i];
            for (int j = i; j < pq->size - 1; j++) {
                pq->tasks[j] = pq->tasks[j + 1];
            }
            pq->size--;
            return task;
        }
    }
    Task highestPriorityTask = pq->tasks[0];
    pq->size--;
    pq->tasks[0] = pq->tasks[pq->size];
    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = left;
        if (right < pq->size && pq->tasks[right].priority > pq->tasks[left].priority) {
            max = right;
        }
        if (pq->tasks[i].priority >= pq->tasks[max].priority) {
            break;
        }
        swap(&pq->tasks[i], &pq->tasks[max]);
        i = max;
    }
    return highestPriorityTask;
}

void displayMenu() {
    printf("\nTask Scheduling Menu:\n");
    printf("1. Add a task\n");
    printf("2. Task to be done\n");
    printf("3. Display all tasks\n");
    printf("4. Save tasks to file\n");
    printf("5. Load tasks from file\n");
    printf("6. Exit\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addTask(PriorityQueue *pq) {
    Task newTask;
    printf("Enter task name: ");
    fgets(newTask.name, sizeof(newTask.name), stdin);
    newTask.name[strcspn(newTask.name, "\n")] = '\0';
    printf("Enter task priority: ");
    scanf("%d", &newTask.priority);
    insert(pq, newTask);
}

void executeTask(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("\nTake some break... You are done with your tasks!\n");
    } else {
        Task executedTask = removeHighestPriority(pq);
        printf("\nTask to be done : %s (priority %d).\n", executedTask.name, executedTask.priority);
    }
}

void displayAllTasks(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("\nTake some break... You are done with your tasks!\n");
    } else {
        printf("\nTo-do list:\n");
        for (int i = 0; i < pq->size; i++) {
            printf("%d. %s (Priority: %d)\n", i + 1, pq->tasks[i].name, pq->tasks[i].priority);
        }
    }
}

void saveTasksToFile(PriorityQueue *pq) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    for (int i = 0; i < pq->size; i++) {
        fprintf(file, "%s %d\n", pq->tasks[i].name, pq->tasks[i].priority);
    }
    fclose(file);
    printf("Tasks saved to file successfully.\n");
}

void loadTasksFromFile(PriorityQueue *pq) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return;
    }
    initialize(pq); // Clear existing tasks
    Task task;
    while (fscanf(file, "%s %d", task.name, &task.priority) == 2) {
        insert(pq, task);
    }
    fclose(file);
    printf("Tasks loaded from file successfully.\n");
}

int main() {
    PriorityQueue pq;
    initialize(&pq);
    int choice;
    bool running = true;
    printf("Welcome to Task Scheduling System!\n");
    while (running) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        switch (choice) {
            case 1:
                clearInputBuffer();
                addTask(&pq);
                break;
            case 2:
                executeTask(&pq);
                break;
            case 3:
                displayAllTasks(&pq);
                break;
            case 4:
                saveTasksToFile(&pq);
                break;
            case 5:
                loadTasksFromFile(&pq);
                break;
            case 6:
                running = false;
                printf("\nThank you for using Task Scheduling System!\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
                break;
        }
        clearInputBuffer();
    }
    return 0;
}
