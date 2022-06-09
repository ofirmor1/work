#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int data;
    struct tree* left;
    struct tree* right;
}tree;

tree* newNode(int data){
    tree* node = (tree*)malloc(sizeof(tree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int isBST(tree* root, int* prev)
{
    if(!root)
    {
        return 1;
    }

    if(!isBST(root->left, prev))
    {
        return 0;
    }

    if(root->data < *prev)
    {
        return 0;
    }

    *prev = root-> data;

    return isBST(root->right, prev);
}
int main(){

	tree *root=newNode(8); 
	root->left= newNode(3); 
	root->right= newNode(10); 
	root->right->right=newNode(14);
	root->right->right->left=newNode(13);
	root->left->left=newNode(1); 
	root->left->right=newNode(6);
	root->left->right->left=newNode(4);
	root->left->right->right=newNode(7);
    int prev = -1;
    int res = isBST(root, &prev);
    printf("%d ", res);
    
}