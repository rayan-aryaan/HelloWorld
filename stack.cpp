//Full implemtation of stack in C
#include <stdio.h>
#include <corecrt_malloc.h>
#define MAX_SIZE 10

typedef struct stack
{
    int* arr;
    int top;
    
}Stack;

Stack* createStack(int size) {
    if(size <= 0) {
        printf("Input error: size less than 1 given\n");
        return NULL;
    }
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->arr = (int*)malloc(size * sizeof(int));
    return stack;

}

int push(Stack* stack, int value) {
    if(stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return -1;
    }
    stack->top++;
    stack->arr[stack->top] = value;
    return 0;
    
}

int pop(Stack* stack) {
    if(stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    int element = stack->arr[stack->top];
    stack->arr[stack->top] = '\0';
    stack->top--;
    return element;

}

int peek(Stack* stack) {
    return stack->arr[stack->top];
}

void display(Stack* stack) {
    for(int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

void destroyStack(Stack* stack) {
    if(stack == NULL) {
        printf("Null pointer exception\n Input Error");
        return;
    }
    free(stack);
}

int main() {
    Stack* stack = createStack(10);
    int choice = 0;
    int element;
    int value;
    while(choice != -1) {
        printf("1. Push an element into Stack\n2. Pop an element from Stack\n3.Peek top element\n4.Display all elements in Stack\n -1 to exit\n");
        printf("\n");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter value of element: ");
                scanf("%d", &value);
                push(stack, value);
                break;
            case 2:
                element = pop(stack);
                printf("Element popped: %d\n", element);
                break;
            case 3:
                element = peek(stack);
                printf("Element on top: %d\n", element);
                break;
            case 4:
                display(stack);
            case -1:
                break;
            default:
                printf("The choice you have entered is not given here\n");

        }
        printf("\n");
    }
    destroyStack(stack);
    return 0;
}