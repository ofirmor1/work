#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"
#define MAGIC_NUMBER 597645

struct Node
{
    int m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct Tree 
{
    Node* m_root;
    int m_magicNumber;
};

Tree* TreeCreate(void)	
{
	Tree* ptrTree;
	if(( ptrTree = (Tree*)malloc(sizeof(Tree))) == NULL)
	{
		return NULL;
	}
	ptrTree->m_root = NULL;
	ptrTree->m_magicNumber = MAGIC_NUMBER;
	return ptrTree;
}

void TreeDestroy(Tree* _tree)
{
	if(_tree)
	{
		TreeDestroy(_tree->m_root->m_left);
		TreeDestroy(_tree->m_root->m_right);
		free(_tree);
	}
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	Tree *temp = NULL;
	if(NULL == _tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_tree->m_root == NULL)
	{
	temp->m_root = (Tree*)malloc(sizeof(Tree));
	temp->m_root->m_left = temp->m_root->m_right = NULL;
	temp->m_root->m_data = _data;
	_tree = temp;
	return ERR_OK;
	}
	if(_data < _tree->m_root->m_data)
	{
		TreeInsert(&(_tree->m_root)->m_left, _data);
	}
	else if(_data > _tree->m_root->m_data)
	{
		TreeInsert(&(_tree->m_root)->m_right, _data);
	}
	return ERR_OK;
	
}

int TreeIsDataFound(Tree* _tree, int _data)
{	
	if(NULL == _tree)
	{
		return 0;
	}
	if(_data == _tree->m_root->m_data)
	{
		return _tree;
	}
	if(_data < _tree->m_root->m_data)
	{
		TreeIsDataFound(&(_tree->m_root)->m_left, _data);
	}
	else if(_data > _tree->m_root->m_data)
	{
		TreeIsDataFound(&(_tree->m_root)->m_right, _data);
	}
	return 1;
}

void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(NULL == _tree)
	{
		printf("Tree is NULL");
	}
	switch(_traverseMode)
	{
		case PRE_ORDER:
		printf("%d\n", _tree->m_root);
		TreePrint((_tree->m_root->m_left),PRE_ORDER);
		TreePrint((_tree->m_root->m_right),PRE_ORDER);
		break;
		
		case IN_ORDER:
		TreePrint((_tree->m_root->m_left),IN_ORDER);
		printf("%d\n", _tree->m_root->m_data);
		TreePrint((_tree->m_root->m_right),IN_ORDER);
		break;
		
		case POST_ORDER:
		TreePrint((_tree->m_root->m_left),POST_ORDER);
		TreePrint((_tree->m_root->m_right),POST_ORDER);
		printf("%d\n", _tree->m_root->m_data);
		break;
	}
}
/*
Node* newNode(int data)
{
  Node* node = (node*)malloc(sizeof(node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->m_father = node;

  return(node);
}*/

