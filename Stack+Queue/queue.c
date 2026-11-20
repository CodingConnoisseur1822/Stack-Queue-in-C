#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Queue {
   struct Node* start;
   struct Node* end;
};

struct Node* createNode(int data, struct Node* end);
struct Queue* createQueue();
void enqueue(struct Queue* queue, int data);
void printQueue(struct Queue* queue);
int dequeue(struct Queue* queue);
void freeQueue(struct Queue* queue);
static int clearInputBuffer(void);

int main(void) {
    struct Queue* queue = createQueue();
    if (queue == NULL) {
        fprintf(stderr, "Failed to initialize queue.\n");
        return 1;
    }

    bool status = true;
    while (status) {
        int option = 0;
        printf("\n---------- Queue Application ----------\n");
        printf("1) Enqueue\n");
        printf("2) Dequeue\n");
        printf("3) Print Queue\n");
        printf("4) Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &option) != 1) {
            printf("Please enter a valid number!\n");
            if (clearInputBuffer()) {
                break;
            }
            continue;
        }
        clearInputBuffer(); 

        switch (option) {
            case 1: {
                int data = 0;
                printf("Enter a number: ");
                if (scanf("%d", &data) != 1) {
                    printf("Invalid number! Enqueue cancelled.\n");
                    if (clearInputBuffer()) {
                        status = false;
                    }
                    break;
                }
                clearInputBuffer();
                enqueue(queue, data);
                break;
            }
            case 2: {
                if (queue->start != NULL) {
                    int value = dequeue(queue);
                    printf("Dequeued value: %d\n", value);
                } else {
                    dequeue(queue); 
                }
                break;
            }
            case 3:
                printQueue(queue);
                break;
            case 4:
                freeQueue(queue);
                queue = NULL;
                printf("Goodbye!\n");
                status = false;
                break;
            default:
                printf("Please enter a choice between 1 and 4!\n");
                break;
        }
    }

    if (queue != NULL) {
        freeQueue(queue);
    }
    return 0;
}

struct Queue* createQueue() {
    struct Queue* queue = malloc(sizeof(*queue));
    if (queue == NULL) {
        printf("Memory Allocation Failed!");
        return NULL;
    }
    (*queue).start = (*queue).end = NULL;
    return queue;
}

void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data, (*queue).end);
    if ((*queue).end == NULL) {
        (*queue).start = (*queue).end = newNode;
        return;
    }
    (*((*queue).end)).next = newNode;
    (*queue).end = newNode;
}

int dequeue(struct Queue* queue) {
    if ((*queue).start == NULL) {
        printf("Empty queue\n");
        return -1;
    }
    struct Node* node = (*queue).start;
    int value = (*node).data;
    (*queue).start = (*(*queue).start).next;

    if ((*queue).start == NULL) {
        (*queue).end = NULL;
    }

    free(node);
    return value;
}

struct Node* createNode(int data, struct Node* end) {
    struct Node* newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory Allocation Failed!");
        return NULL;
    }
    (*newNode).data = data;
    (*newNode).next = NULL;
    (*newNode).prev = end;
    return newNode;
}

void freeQueue(struct Queue* queue) {
    while ((*queue).start != NULL) {
        dequeue(queue);
    }
    free(queue);
}


void printQueue(struct Queue* queue) {
    struct Node* node = (*queue).start;
    printf("Queue: ");
    while (node) {
        printf("%d ", (*node).data);
        node = (*node).next;
    }
    printf("\n");
}

static int clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        
    }
    return ch == EOF;
}
