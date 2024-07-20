#include <stdio.h>
#include <stdlib.h>

// Node structure definition for BST
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into BST
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

// Function to perform inorder traversal of BST
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to search for a value in BST
Node* search(Node* root, int key) {
    // Base cases: root is null or key is present at root
    if (root == NULL || root->data == key) {
        return root;
    }
    
    // Key is greater than root's data; search in right subtree
    if (key > root->data) {
        return search(root->right, key);
    }
    
    // Key is smaller than root's data; search in left subtree
    return search(root->left, key);
}

// Function to find the minimum value node in a BST
Node* minValueNode(Node* node) {
    Node* current = node;
    
    // Loop down to find the leftmost leaf
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

// Function to delete a node from BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    
    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    // If key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(root->right);
        
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Driver program to test BST creation, searching, and deletion
int main() {
    int values[] = {45, 15, 79, 90, 10, 55, 12, 20, 50};
    int n = sizeof(values) / sizeof(values[0]);
    
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, values[i]);
    }
    
    printf("Inorder traversal of BST: ");
    inorder(root);
    printf("\n");
    
    int searchKey = 50;
    Node* searchResult = search(root, searchKey);
    if (searchResult != NULL) {
        printf("Node with key %d found in BST.\n", searchKey);
    } else {
        printf("Node with key %d not found in BST.\n", searchKey);
    }
    
    int deleteKey = 45;
    root = deleteNode(root, deleteKey);
    
    printf("Inorder traversal of BST after deletion of key %d: ", deleteKey);
    inorder(root);
    printf("\n");
    
    return 0;
}