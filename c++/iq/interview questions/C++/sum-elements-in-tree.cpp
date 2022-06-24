#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Tree{
    int data;
    Tree *left;
    Tree *right;
}Tree;

Tree* newnode(int data)
{ 
	Tree* node = new Tree;
	node->data = data; 
	node->left = NULL; 
	node->right = NULL; 

	return node; 
} 

int sumElementsOfTree(Tree* node)
{
    if(!node)
    {
        return 0;
    }
    unsigned int sum;
    return node->data + sumElementsOfTree(node->left) + sumElementsOfTree(node->right);
}

void printTree(Tree* root)
{
    queue<Tree*> q;
    Tree* temp;
    q.push(root);
    q.push(NULL);
    cout << "root" << endl;
    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        if(!temp)
        {
            if(!q.empty())
            {
                cout << "\nnext level" << endl;
                q.push(NULL);
            }   
        }
        else
        {
            cout << temp->data << ' ';
            if(temp->left)
            {
                q.push(temp->left);
            }
            if(temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}

int main() 
{ 
    Tree *root=newnode(10); 
	root->left= newnode(-2); 
	root->right= newnode(8); 
	root->right->right=newnode(5);
	root->right->left=newnode(-7);
	root->left->left=newnode(6); 
	root->left->right=newnode(-5);

	cout<<"\noriginal tree...\n"<<endl; 
	printTree(root);

    unsigned int sum = sumElementsOfTree(root);

    cout << "\n\nsum of elements : " << sum << endl;

	return 0; 
} 