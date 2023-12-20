#include <stdio.h>
#include <stdlib.h>
 
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
 
TreeNode* createNode(int value) {
    struct TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
 
    if (newNode == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
 
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
 
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
 
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value >= root->data) {
        root->right = insert(root->right, value);
    }
 
    return root;
}
 
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
 
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}
 
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}
 
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
 
    struct TreeNode* queue[100] = { 0 };
    int front = 0, rear = 0;
 
    queue[rear++] = root;
 
    while (front < rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->data);
 
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
 
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
}
 
int main() {
    TreeNode* root = NULL;
 
    int n, value;
 
    printf("Unesite broj elemenata: ");
    scanf_s("%d", &n);
 
    printf("Unesite vrednosti elemenata:\n");
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &value);
        root = insert(root, value);
    }
 
    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");
 
    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");
 
    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");
 
    printf("Level order traversal: ");
    levelOrderTraversal(root);
    printf("\n");
 
    return 0;
}
