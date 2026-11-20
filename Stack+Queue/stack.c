#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

struct Stack {
    struct Node* top;
};

struct Node* createNode(int data, struct Node* next);
struct Stack* createStack(void);
void push(int data, struct Stack* stack);
int pop(struct Stack* stack);
int peek(struct Stack* stack);
void printStack(struct Stack* stack);
int isEmpty(struct Stack* stack);
void free_stack(struct Stack* stack);
static int clearInputBuffer(void);

int main(void) {
    struct Stack* stack = createStack();
    if (stack == NULL) {
        fprintf(stderr, "Failed to initialize stack.\n");
        return 1;
    }

    bool status = true;
    while (status) {
        int option = 0;
        printf("\n---------- Stack Application ----------\n");
        printf("1) Push\n");
        printf("2) Pop\n");
        printf("3) Peek\n");
        printf("4) Print Stack\n");
        printf("5) Exit\n");
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
                    printf("Invalid number! Push cancelled.\n");
                    if (clearInputBuffer()) {
                        status = false;
                    }
                    break;
                }
                clearInputBuffer();
                push(data, stack);
                break;
            }
            case 2: {
                if (!isEmpty(stack)) {
                    int value = pop(stack);
                    printf("Popped value: %d\n", value);
                } else {
                    pop(stack);
                }
                break;
            }
            case 3: {
                if (!isEmpty(stack)) {
                    int value = peek(stack);
                    printf("Top value: %d\n", value);
                } else {
                    peek(stack);
                }
                break;
            }
            case 4:
                printStack(stack);
                break;
            case 5:
                free_stack(stack);
                stack = NULL;
                printf("Goodbye!\n");
                status = false;
                break;
            default:
                printf("Please enter a choice between 1 and 5!\n");
                break;
        }
    }

    if (stack != NULL) {
        free_stack(stack);
    }
    return 0;
}

struct Stack* createStack(void) {
    struct Stack* stack = malloc(sizeof(*stack));
    if (stack == NULL) {
        printf("Memory Allocation Failed!\n");
        return NULL;
    }
    (*stack).top = NULL;
    return stack;
}

struct Node* createNode(int data, struct Node* next) {
    struct Node* newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Memory Allocation Failed!\n");
        return NULL;
    }
    (*newNode).data = data;
    (*newNode).next = next;
    (*newNode).prev = NULL;
    return newNode;
}

int isEmpty(struct Stack* stack) {
    return stack == NULL || (*stack).top == NULL;
}

void push(int data, struct Stack* stack) {
    if (stack == NULL) {
        return;
    }
    struct Node* newNode = createNode(data, (*stack).top);
    if (newNode == NULL) {
        return;
    }
    if ((*stack).top != NULL) {
        (*(*stack).top).prev = newNode;
    }
    (*stack).top = newNode;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is EMPTY!\n");
        return -1;
    }

    struct Node* temp = (*stack).top;
    int value = (*temp).data;
    (*stack).top = (*temp).next;

    if ((*stack).top != NULL) {
        (*(*stack).top).prev = NULL;
    }

    free(temp);
    return value;
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Empty Stack!\n");
        return -1;
    }
    return (*(*stack).top).data;
}

void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack - Top to Bottom: (empty)\n");
        return;
    }

    struct Node* currentNode = (*stack).top;
    printf("Stack - Top to Bottom: ");
    while (currentNode != NULL) {
        printf("%d ", (*currentNode).data);
        currentNode = (*currentNode).next;
    }
    printf("\n");
}

void free_stack(struct Stack* stack) {
    if (stack == NULL) {
        return;
    }
    while (!isEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}

static int clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
    return ch == EOF;
}