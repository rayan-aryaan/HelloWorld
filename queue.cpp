#include <stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct Queue
{
    int front;
    int rear;
    int* arr;
    int maxSize;
}Queue;

Queue* createQueue(int noOfElements) {
    Queue* queue =(Queue*)malloc(sizeof(Queue));
    queue->maxSize = noOfElements;
    queue->arr = (int*)malloc(queue->maxSize * sizeof(int));
    queue->front = 0;
    queue->rear = 0;
    memset(queue->arr, NULL, queue->maxSize);
    return queue;
    
}
int getSize(Queue* queue){
    if(queue->rear >= queue->front){ 
        return queue->rear - queue->front + 1;
    }
    return queue->maxSize - queue->front + queue->rear + 1;
}

bool isEmpty(Queue* queue){
    return (queue->rear == queue->front) && queue->arr[queue->front] == NULL;
}
void enQueue(Queue* queue, int value) {
    if(isEmpty(queue)){
        queue->arr[0] = value;
        return;
    }
    if(getSize(queue) == queue->maxSize) {
        printf("Queue is full\n");
        return;
    }
    if(queue->rear == queue->maxSize - 1){
        queue->rear = 0;
        queue->arr[queue->rear] = value;
        return;
    }
    queue->rear++;
    queue->arr[(queue->rear)] = value;
    return;
}

int deQueue(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty\n");
        return NULL;
    }
    int element = queue->arr[queue->front];
    if(queue->front == queue->maxSize - 1){
        queue->arr[queue->front] = NULL;
        queue->front = 0;
        return element;
    }
    queue->arr[queue->front] = NULL;
    queue->front++;
    return element;
}

void display(Queue* queue){
    if(queue->front > queue->rear){
        for(int i = queue->front; i < queue->maxSize; i++){
            printf("%d ", queue->arr[i]); 
        }
        for(int i = 0; i <= queue->rear; i++){
            printf("%d ", queue->arr[i]); 
        }
    }
    else if(queue->rear >= queue->front){
        for(int i = queue->front; i <= queue->rear; i++){
            printf("%d ", queue->arr[i]); 
        }
    }
    printf("\n");

}

int peek(Queue* queue){
    return queue->arr[queue->front];
}
int returnFront(Queue* queue){
    return queue->front;
}

int returnRear(Queue* queue){
    return queue->rear;
}

void destroyQueue(Queue* queue) {
    if(queue != NULL){
        free(queue->arr);
        free(queue);
    }
    
}

int main(){
    printf("How many elements should the queue store at max?");
    int choice = 0;
    scanf("%d", &choice);
    Queue* queue = createQueue(choice);
    choice = 0;
    int element;
    while(choice != -1){
        printf("What operation would you like to do with the queue(-1 to exit)?\n1.Enqueue\n2.Dequeue\n3.Peek\n4.Display\n5.Front\n6.Rear\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nEnter element value: ");
            scanf("%d", &element);
            enQueue(queue, element);
            break;
        case 2:
            element = deQueue(queue);
            printf("\nElement dequeued: %d\n", element);
            break;
        case 3:
            element = peek(queue);
            printf("\nElement at front: %d\n", element);
            break;
        case 4:
            printf("\n");
            display(queue);
            break;
        case 5:
            element = returnFront(queue);
            printf("\nFront ptr value: %d\n", element);
            break;
        case 6:
            element = returnRear(queue);
            printf("\nRear ptr value: %d\n", element);
            break;
        case -1:
            break;
        default:
            printf("Invalid operation choosen.\n");
            break;
        }
    }
    destroyQueue(queue);
    return 0;

}


