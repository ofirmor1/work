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

void nodesWithoutSiblings(Tree* root)
{
    queue<Tree*> q;
    q.push(root);
    vector<int> store;
    Tree* temp;

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        // cout << temp->data << ' ';; //print the data
        if(!(temp->left) && temp->right)
        {
            store.push_back(temp->right->data);
        }
        if(temp->left && !(temp->right))
        {
            store.push_back(temp->left->data);
        }
        if(temp->right)
        {
            q.push(temp->right);
        }
        if(temp->left)
        {
            q.push(temp->left);
        }
    }
    if(store.size() == 0)
    {
        cout << "-1, no such node" << endl;
    }
    sort(store.begin(), store.end());
    for(auto e : store)
    {
        cout << e << ' ';
    }
}

int main() 
{ 
	//**same tree is builted as shown in example**
	cout<<"same tree is built as shown in example\n";
	Tree *root=newnode(2); 
	root->left= newnode(7); 
	root->right= newnode(5); 
	root->right->right=newnode(9);
	root->right->right->left=newnode(4);
	root->left->left=newnode(2); 
	root->left->right=newnode(6);
	root->left->right->left=newnode(5);
	root->left->right->right=newnode(11);

	cout<<"printing the nodes that don't have sibling...\n"<<endl; 
	nodesWithoutSiblings(root);

	return 0; 
} 