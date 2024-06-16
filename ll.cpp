//Linked list implemtation in C
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef struct Node{

    int data;
    Node* next;

}Node;

typedef struct ll
{
    Node* head;

}LinkedList;

Node* createNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

LinkedList* createLinkedList(int data){
    LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head = createNode(data);
    return ll;
}

int length(LinkedList* ll){
    if(ll->head->next == NULL){
        return 1;
    }
    Node* node = ll->head;
    int length = 0;
    while(node != NULL){
        node = node->next;
        length++;
    }
    return length;
}


int addNodeAtEnd(LinkedList* ll, int data){

    Node* node = ll->head;
    Node* newNode = createNode(data);
    if(node->next == NULL){
        node->next = newNode;
        return 0;
    }
    while(node->next != NULL){
        node = node->next;
    }
    node->next = newNode;
    return 0;
}

int addNodeAtFirst(LinkedList* ll, int data){
    Node* newNode = createNode(data);
    newNode->next = ll->head;
    ll->head = newNode;
    return 0;
}

int addNodeinBetween(LinkedList* ll, int data, int pos ){ // pos is same as array pos
    if(pos >= length(ll)){
        printf("Position given is outside the length of linked list. Please give valid position\n");
        return NULL;
    }
    Node* temp = ll->head;
    Node* prev = temp;
    Node* newNode = createNode(data);
    for(int i = 0; i < pos; i++){
        prev = temp;
        temp = temp->next;
    }
    prev->next = newNode;
    newNode->next = temp;
    return 0;
}

int deleteNodeAtEnd(LinkedList* ll){
    if(ll->head->next == NULL){
        printf("Cannot delete as only head remains\n");
        return NULL;
    }
    Node* node = ll->head;
    Node* prev = node;
    while(node->next != NULL){
        prev = node;
        node = node->next;
    }
    prev->next = NULL;
    int element = node->data;
    free(node);
    return element;
}

int deleteNodeAtBegginning(LinkedList* ll){
    if(ll->head->next == NULL){
        printf("Cannot delete as only head remains\n");
        return NULL;
    }
    Node* temp = ll->head;
    ll->head = ll->head->next;
    int element = temp->data;
    free(temp);
    return element;
}

int deleteNodeinBetween(LinkedList* ll, int pos){
    if(pos >= length(ll)){
        printf("Position given is outside the length of linked list. Please give valid position\n");
        return NULL;
    }
    if(ll->head->next == NULL){
        printf("Cannot delete as only head remains\n");
        return NULL;
    }
    Node* temp = ll->head;
    Node* prev = temp;
    for(int i = 0; i < pos; i++){
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    int element = temp->data;
    free(temp);
    return element;
}

int deleteNodeByValue(LinkedList* ll, int value){
    if(ll->head->next == NULL){
        printf("Cannot delete as only head remains\n");
        return NULL;
    }
    if(ll->head->data == value){
        deleteNodeAtBegginning(ll);
        return 0;
    }
    Node* temp = ll->head;
    Node* prev = temp;
    while(temp->data != value && temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    if(temp->data != value){
        printf("Unable to find such a value in LinkedList\n");
        return NULL;
    }
    prev->next = temp->next;
    free(temp);
    return 0;
}

int* search(LinkedList* ll, int data){
    Node* temp = ll->head;
    int pos = 0;
    int* finalResult = (int*)malloc(2 * sizeof(int));
    while(temp->data != data && temp != NULL){
        temp = temp->next;
        pos++;
    }
    if(temp == NULL){
        printf("Unable to find such a value in LinkedList\n");
        return NULL;
    }
    finalResult[0] = temp->data;
    finalResult[1] = pos;
    return finalResult;
}

int modify(LinkedList* ll, int data, int pos){
    Node* temp = ll->head;
    if(pos >= length(ll)){
        return NULL;
    }
    for(int i = 0; i < pos; i++){
        temp = temp->next;
    }
    temp->data = data;
    return 0;
}

void display(LinkedList* ll){
    Node* temp = ll->head;
    while(temp != NULL){
        if(temp->next == NULL){
            printf("%d", temp->data);
        }
        else{
            printf("%d->", temp->data);
        }
        temp = temp->next;
    }
    printf("\n");
}

void destroyLinkedList(LinkedList* ll){
    free(ll);
}

int main(){
    int choice = 0;
    int element = 0;
    int choiceIn = 0;
    int pos = 0;
    int returnValue = -1;
    int* searchResult;
    printf("What is the value of head?");
    scanf("%d",&element);
    LinkedList* ll = createLinkedList(element);
    while(choice != -1){
        printf("What would you like to do with your Linked List?(-1 to exit)\n1. Add an element\n2. Delete an element\n3. Search for an element\n4. Modify value at a position\n5. Return length\n6.Display all elements\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter value of element: ");
            scanf("%d", &element);
            printf("Would you like to:\n1. Add at beggining\n2. Add at end\n3. Add in between\n");
            scanf("%d", &choiceIn);
            switch (choiceIn)
            {
            case 1:
                returnValue = addNodeAtFirst(ll, element);
                break;
            case 2:
                returnValue = addNodeAtEnd(ll, element);
                break;
            case 3:
                printf("Which position to enter? ");
                scanf("%d", &pos);
                returnValue = addNodeinBetween(ll,element, pos);
                break;
            default:
                printf("Please choose a valid option\n");
                break;
            }
            if(returnValue != NULL){
                    printf("Added element successfully\n");
                }
            break;
        case 2:
            printf("Would you like to:\n1. Delete at beggining\n2. Delete at end\n3. Delete in between\n4. Delete by value\n");
            scanf("%d", &choiceIn);
            switch(choiceIn){
                case 1:
                    returnValue = deleteNodeAtBegginning(ll);
                    break;
                case 2:
                    returnValue = deleteNodeAtEnd(ll);
                    break;
                case 3:
                    printf("Which position to delete? ");
                    scanf("%d", &pos);
                    returnValue = deleteNodeinBetween(ll, pos);
                    break;
                case 4:
                    printf("Which value to delete? ");
                    scanf("%d", &pos);
                    returnValue = deleteNodeByValue(ll, pos);
                    break;
            }
            if(returnValue != NULL){
                if(choiceIn != 4){
                    printf("Deleted element %d successfully\n", returnValue);
                }
                else{
                    printf("Deleted the value successfully\n");
                }
            }
            break;

        case 3:
            printf("Which element would you like to search for? ");
            scanf("%d", &element);
            searchResult = search(ll, element);
            if(searchResult != NULL){
                printf("Found element %d at position %d sucessfully\n", searchResult[0], searchResult[1]);
                free(searchResult);
            }
            break;

        case 4:
            printf("Which position would you like to modify? ");
            scanf("%d", &pos);
            printf("What is the value you would like to change it to? ");
            scanf("%d", &element);
            returnValue = modify(ll, element, pos);
            if(returnValue != NULL){
                printf("Value modified at position %d successfully\n", pos);
            }
            break;

        case 5:
            element = length(ll);
            printf("Length of Linked List: %d\n", element);
            break;

        case 6:
            display(ll);
            break;

        case -1:
            break;
        
        default:
            printf("Please enter a valid option\n");
            break;
        }


    }
    destroyLinkedList(ll);
    return 0;

}


