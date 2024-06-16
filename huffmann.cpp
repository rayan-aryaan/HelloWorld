#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
        

/*
typedef struct left{
    enum { NODE_TYPE, INTERNAL_NODE_TYPE } leftType;
    union {
        InternalNode* leftInternalNode;
        Node* leftNode;
    }left;
}Left;

typedef struct right{
    enum { NODE_TYPE, INTERNAL_NODE_TYPE } rightType;
    union {
        InternalNode* rightInternalNode;
        Node* rightNode;
    }right;
}Right;

typedef struct InternalNode{

    int data;
    Left* left;
    Right* right;

}Node;

typedef struct Element{
    enum { NODE_TYPE, INTERNAL_NODE_TYPE } elementType;
    union {
        InternalNode* internalNodeElement;
        Node* NodeElement;
    } element;

}Element;
*/

typedef struct Node{

    int data;
    char c;
    Node* left;
    Node* right;

}Node;

typedef struct Queue{

    Node* elements;
    int size;

}Queue;

typedef struct BinaryData{

    unsigned char* byte;
    int totalBits;
    int length;

}BinaryData;

char convertUpperToLower(char c) {
    return c + 32;
}

int returnSumOfElementData(Node* el1, Node* el2) {
    return el1->data + el2->data;
}

int length(char* str){
    int count = 0;
    while(str[count] != '\0'){
        count++;
    }
    return count;
}

int charCount(char letter, char* str) {
    char compare = 'a';
    int i = 0;
    int count = 0;
    while(compare != '\0') {
        compare = str[i];
        if(compare == '\0') {
            break;
        }
        if(compare == letter) {
            count++;
        }
        i++;
    }
    return count;

}


Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->c = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* createNode(int data, char c) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->c = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroyNode(Node* node) {
    free(node);
}

void freeTree(Node* root) {
    if(root == NULL) {
        return;
    }
    if(root->left != NULL) {
        freeTree(root->left);
    }
    if(root-> right != NULL) {
        freeTree(root->right);
    }
    destroyNode(root);
}

Queue* createQueue(Dictionary* dict) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->size = 0;
    queue->elements = (Node*)malloc(sizeof(Node) * dict->size);
    memset(queue->elements, 0, sizeof(Node) * dict->size);
    return queue;
}

void destroyQueue(Queue* queue) {
    free(queue->elements);
    free(queue);
}

BinaryData* createBinary(int heightOfTree, int length){
    BinaryData* binary = (BinaryData*)malloc(sizeof(BinaryData));
    int bitArraySize = (heightOfTree * length + 7) / 8; // Number of bytes needed
    binary->byte = (unsigned char*)calloc(bitArraySize, sizeof(unsigned char));
    binary->totalBits = heightOfTree * length;
    binary->length = 0;
    return binary;

}

void destroyBinary(BinaryData* binary){
    free(binary->byte);
    free(binary);
}



bool searchNode(Node* root, char c){
    if (root == nullptr) {
        return false;
    }

    if (root->c == c) {
        return true;
    }

    // Recursively search in the left and right subtrees
    bool foundInLeft = searchNode(root->left, c);
    if (foundInLeft) {
        return true;
    }

    bool foundInRight = searchNode(root->right, c);
    return foundInRight;
}

int findHeight(Node* root){
    if(root == NULL) {
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}




Queue* enQueue(Queue* queue,Node* element) {
    int i = 0;
    while (i < queue->size) {
        int currentData = queue->elements[i].data;
        int newData = element->data;
        if (newData >= currentData) {
            i++;
        } 
        else {
            break;
        }
    }

    for (int j = queue->size - 1; j >= i; j--) {
        queue->elements[j + 1] = queue->elements[j];
    }

    queue->elements[i] = *element;
    queue->size++;
    return queue;
}



void printQueue(Queue* queue) {
    Node element;
    int data;
    char c;
    for(int i = 0; i < queue->size; i++) {
        element = queue->elements[i];
        printf("%c, %d\n", element.c, element.data);
    }
             
}

Node* deQueue(Queue* queue) {
    Node* element;
    int data;
    char c;
    if(queue->size > 0) {
        data = queue->elements[0].data;
        if(queue->elements[0].c != NULL){
            c = queue->elements[0].c;
            element = createNode(data, c);
        }
        else{
            element = createNode(data);
        }
        if(queue->elements[0].left != NULL){
            element->left = queue->elements[0].left;
        }
        if(queue->elements[0].right != NULL){
            element->right = queue->elements[0].right;
        }
        for(int i = 0; i < queue->size - 1; i++) {
            queue->elements[i] = queue->elements[i + 1];
        }
        queue->size--; 
    }
    return element;
    
}

void printTree(Node* root){
    //preorder print
    if(root->c == NULL){
        printf("%d\n", root->data);

    }
    if(root->c != NULL){
        printf("%c, %d\n", root->c, root->data);
    }
    if(root->left != NULL){
        printTree(root->left);
    }
    if(root->right != NULL){
        printTree(root->right);
    }
    

}

char* getHuffmannCode(Node* root, char c, int height) {
    // search root->left side if node exsits fo sho
    // if yes add 0 then search root->left tree and repeat
    // if no go search root->right if node exists if yes 1
    char* huffmannCode = (char*)calloc(height + 1, sizeof(char));
    Node* temp = root;
    while(temp != NULL) {
        if(temp->c == c){
            return huffmannCode;
        }
        if(temp->left != NULL) {
            if(searchNode(temp->left, c)) {
                strcat(huffmannCode, "0");
                temp = temp->left;
            }
        }
        if(temp->right != NULL) {
            if(searchNode(temp->right, c)) {
                strcat(huffmannCode, "1");;
                temp = temp->right;
            }
        }  
    }
    return huffmannCode;
}

void setBit(BinaryData* binary, char value, int index) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    if(value == '0') {
        binary->byte[byteIndex] &= ~(1 << bitIndex);
    }
    if(value == '1') {
        binary->byte[byteIndex] |= (1 << bitIndex);
    }
    binary->length++;

}

int getBit(BinaryData* binary, int index) {
    int byteIndex = index / 8;
    int bitIndex = index % 8;
    return (binary->byte[byteIndex] >> bitIndex) & 1;
}

void printBinary(BinaryData* binary) {
    for (int i = 0; i < binary->length; i++) {
        printf("%d", getBit(binary, i));
    }
    printf("\n");
}

void printTextFromBinary(BinaryData* binary, Node* root) {
    int value = -1;
    Node* temp = root;
    for (int i = 0; i < binary->length; i++) {
        value = getBit(binary, i);
        if(value == 0) {
            temp = temp->left;
        }
        if (value == 1) {
            temp = temp->right;
        }
        if (temp->c != NULL) {
            printf("%c", temp->c);
            temp = root;
        }
    }
    printf("\n");

}


Dictionary* countEachCharInString(char* str) {
    int i = 0;
    int count = 0;
    Dictionary* dictionary = createDictionary();
    char alphabets [26]= {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    while(str[i] != '\0')   {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = convertUpperToLower(str[i]);
        }
        i++;
    }
    for(i = 0; i < 26; i++) {
        count = charCount(alphabets[i], str);
        if(count != 0) {
            // put alphabets[i] and count together like a dict;
            addToDictionary(dictionary, alphabets[i], count);

        }
        count = 0;
    }
    return dictionary;
}

//create a tree from the dictionary, then delete dictionary and return tree

Node* createHuffmannTree(Dictionary* dict) {
    int data;
    Entry* entry = dict->entry;
    Node* node;
    Node* node1;
    Node* node2;
    Queue* queue = createQueue(dict);
    for(int i = 0; i < dict->size; i++) {
        node = createNode(entry[i].value, entry[i].key);
        queue = enQueue(queue, node); //make priority queue of leaf nodes     
        destroyNode(node);
    }
    // pop 2 lowest frequencies of the queue, make node
    while(queue->size > 1) {
        node1 = deQueue(queue);
        node2 = deQueue(queue);
        data = returnSumOfElementData(node1, node2);
        node = createNode(data);
        node->left = node1;
        node->right = node2;
        queue = enQueue(queue, node);
    }
    Node* root = deQueue(queue);
    destroyQueue(queue);
    freeDictionary(dict);
    return root;
}


BinaryData* createHuffmannCodeFromTree(Node* root, char* str) {
    //using tree made previously, create the huffmann code
    //transverse until hit leaf node, direction taken gives 0 or 1 
    int len = length(str);
    int height = findHeight(root);
    char c;
    char* huffmannCodeFromChar = NULL;
    int lenOfHuffmanCodeFromChar = 0;
    BinaryData* huffmannCode = createBinary(height, len);
    for(int i = 0; i < len; i++){
        c = str[i];
        // make getHuffmanCode func for every character;
        huffmannCodeFromChar = getHuffmannCode(root, c, height);
        printf_s("%c: %s\n", c, huffmannCodeFromChar); // verify correct code for each char
        // make setBit func to put the 0s and 1s in huffmannCode
        lenOfHuffmanCodeFromChar = length(huffmannCodeFromChar);
        for(int j = 0; j < lenOfHuffmanCodeFromChar; j++){
            setBit(huffmannCode, huffmannCodeFromChar[j], huffmannCode->length);
        }
        free(huffmannCodeFromChar);
        huffmannCodeFromChar = NULL;
    }
    return huffmannCode;
}



BinaryData* createHuffmannCodeFromString(char* str) {
    //does the full code from start to finish
    //should return the full code as well as the tree so that we can decode and get original message
    // for now just return the code & free the tree
    // make printBInary for main
    Dictionary* dict = countEachCharInString(str);
    Node* root = createHuffmannTree(dict);
    BinaryData* huffmannCode = createHuffmannCodeFromTree(root, str);
    printBinary(huffmannCode);
    printTextFromBinary(huffmannCode,  root);
    freeTree(root);
    return huffmannCode;
}

int main() {
    char str[32];
    printf("What string would you like to convert to Huffmann Code: ");
    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    printf("String entered: %s\n", str);
    BinaryData* huffmannCode = createHuffmannCodeFromString(str);
    destroyBinary(huffmannCode);
    return 0;
}

/*
int maintest3() {
    // test the huffmannTreeCreation
    // make a printTree function to check
    // check memory management asw
    char str[32];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    printf("String entered: %s\n", str);
    Dictionary* dict = createDictionary();
    dict = countEachCharInString(str);
    Node* root = createHuffmannTree(dict);
    printf("Tree created: \n");
    printTree(root);
    printf("Dictionary storage way: \n");
    printDictionary(dict);
    freeDictionary(dict);
    return 0;
}

*/
/*
int maintest2() {
    //test enQueue to see if adding right, make printQUeue() function to check
    char str[32];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    printf("String entered: %s\n", str);
    Dictionary* dict = createDictionary();
    dict = countEachCharInString(str);
    Node* node;
    Queue* queue = createQueue(dict);
    for(int i = 0; i < dict->size; i++) {
        node->c = dict->entry[i].key;
        node->data = dict->entry[i].value;
        queue = enQueue(queue, node);
    }
    printQueue(queue);
    printf("Dictionary storage way: \n");
    printDictionary(dict);
    destroyQueue(queue);
    freeDictionary(dict);
    return 0;

}
*/
/*
int testmain() {
    char str[32];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    printf("String entered: %s\n", str);
    Dictionary* dict = countEachCharInString(str);
    printDictionary(dict);
    return 0;
}

*/