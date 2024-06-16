#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

    int data;
    Node* left;
    Node* right;

}Node;

typedef struct Tree{

    Node* root;

}Tree;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree* createTree(int data) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = createNode(data);
    return tree;
}

void addNode(Node** root, int data) {
    if((*root)->data == data) {
        printf("Cannot add duplicates\n");
        return;
    }
    if((*root)->data < data) {
        if((*root)->right != NULL) {
            addNode(&((*root)->right), data);
        }
        else {
            (*root)->right = createNode(data);
            printf("Added successfully\n");
        }
        
    }
    if((*root)->data > data) {
         if((*root)->left != NULL) {
            addNode(&((*root)->left), data);
         }
         else {
            (*root)->left = createNode(data);
            printf("Added successfully\n");
         }
        
    }

}

Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        printf("Node not found\n");
        return root;
    }

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            printf("Node deleted\n");
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            printf("Node deleted\n");
            return temp;
        }

        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void preOrderTransversal(Node* root){
    printf("%d\n", root->data);
    if(root->left != NULL){
        preOrderTransversal(root->left);
    }
    if(root->right != NULL){
        preOrderTransversal(root->right);
    }
}

void InOrderTransversal(Node* root){
    if(root->left != NULL){
        InOrderTransversal(root->left);
    }
    printf("%d\n", root->data);
    if(root->right != NULL){
        InOrderTransversal(root->right);
    }
}

void PostOrderTransversal(Node* root){
    if(root->left != NULL){
        PostOrderTransversal(root->left);
    }
    if(root->right != NULL){
        PostOrderTransversal(root->right);
    }
    printf("%d\n", root->data);
}

void searchNode(Node* root, int data){
    if(root->left != NULL && root->data != data) {
        searchNode(root->left, data);
    }
    if(root->right != NULL && root->data != data) {
        searchNode(root->right, data);
    }
    if(root->data != data) {
        printf("Node not found\n");
        return;
    }
    printf("Node found\n");
}

int main(){
    int val;
    int choice = 0;
    printf("What is the value of Root Node? ");
    scanf("%d", &val);
    Tree* tree = createTree(val);
    while(choice != -1){
        printf("What operations to do on Tree? (-1 to exit)\n1.Add a node\n2.Delete a node\n3. Search for a node\n4. Transverse the node\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("What is the value of node? ");
                scanf("%d", &val);
                addNode(&(tree->root), val);
                break;
            case 2:
                printf("What is the value of the node that is to be deleted? ");
                scanf("%d", &val);
                deleteNode(tree->root, val);
                break;
            case 3:
                printf("What is the value of the node that is to be searched? ");
                scanf("%d", &val);
                searchNode(tree->root, val);
                break;
            case 4:
                printf("What method of transversal?\n1.PreOrder\n2.InOrder\n3.PostOrder ");
                scanf("%d", &val);
                switch(val){
                    case 1:
                        preOrderTransversal(tree->root);
                        break;
                    case 2:
                        InOrderTransversal(tree->root);
                        break;
                    case 3:
                        PostOrderTransversal(tree->root);
                        break;

                }
                break;
            case -1:
                break;
            default:
                printf("Enter a valid option\n");
                break;

        }
    }
    return 0; 
}