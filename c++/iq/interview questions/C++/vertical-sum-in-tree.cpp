#include <iostream>
#include <map>

using namespace std;

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

void findVerticalSum(tree* root, int col, map<int,int>& hash)
{
    if(!root)
    {
        return;
    }

    hash[col] += root->data;
    findVerticalSum(root->left, col - 1, hash);
    findVerticalSum(root->right, col + 1, hash);
}

void verticalSum(tree* root)
{
    map<int,int>* hash = new map<int,int>;
    findVerticalSum(root, 0, *hash);
    
    for(auto const& pair : *hash)
    {
        cout << pair.first << '\t'<<pair.second << endl;
    }
}
int main(){

	tree *root=newNode(2); 
	root->left= newNode(7); 
	root->right= newNode(5); 
	root->right->right=newNode(9);
	root->right->right->left=newNode(4);
	root->left->left=newNode(2); 
	root->left->right=newNode(6);
	root->left->right->left=newNode(5);
	root->left->right->right=newNode(11);

    verticalSum(root);
    
}