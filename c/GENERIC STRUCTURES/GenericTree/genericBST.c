#include <stdio.h>
#include <stdlib.h>
#include "genericBST.h"

typedef struct Node Node;

struct Node
{
    void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct BSTree 
{
    Node m_root;
	LessComparator m_lessThan;
};

/******************************************************/
/*******************Inner Functions********************/
/******************************************************/
static Node* CreateNode(void* _item);
static void DestroyTreeRec(Node* _root, void (*_destroyer)(void*));
static Node* FindFatherOfNode(Node* _node, void* _item, LessComparator _less);
static BSTreeItr InsertNode(BSTree*_tree, Node* _father,void* _item, LessComparator _less);
static int IsLeaf(Node* _node);
static void* RemoveLeaf(Node* _node);
static int OnlyOneChild(Node* _node);
static void* RemoveNodeWithOneChild(Node* _node);
static void SwapNodesData(Node* _n1, Node* _n2);
static BSTreeItr BSTree_ForEach_PREORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_INORDER(Node* _node, ActionFunction _action, void* _context);
static BSTreeItr BSTree_ForEach_POSTORDER(Node* _node, ActionFunction _action, void* _context);


/****************************************************/
BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* ptrTree;
	if(NULL == _less)
	{
		return NULL;
	}
	if(( ptrTree = (BSTree*)malloc(sizeof(BSTree))) == NULL)
	{
		return NULL;
	}
	ptrTree->m_lessThan = _less;
	ptrTree->m_root.m_data = NULL;
	ptrTree->m_root.m_left = NULL;
	ptrTree->m_root.m_right = NULL;
	ptrTree->m_root.m_father = &ptrTree->m_root;

	return ptrTree;
}
/****************************************************/
void  BSTree_Destroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if(!_tree  ||  !*_tree)
	{
		return;
	}
	if((*_tree)->m_root.m_left != NULL)
	{
		DestroyTreeRec((*_tree)->m_root.m_left, _destroyer);
	}
	free(*_tree);
	*_tree = NULL;
}
/****************************************************/
BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	BSTree* ptrTree;
	Node *fatherPtr = NULL;
	if(NULL == _tree)
	{
		return NULL;
	}
	if(NULL == _item)
	{
		return (BSTreeItr) &_tree->m_root;
	}
	if(NULL == _tree->m_root.m_left)
	{
		_tree->m_root.m_left = CreateNode(_item);
		if(NULL == (_tree->m_root.m_left))
		{
			return (BSTreeItr) &_tree->m_root;
		}
		_tree->m_root.m_left->m_father = &_tree->m_root;

		return (BSTreeItr) &_tree->m_root.m_left;
	}

	fatherPtr = FindFatherOfNode(_tree->m_root.m_left, _item, _tree->m_lessThan);
	if(NULL == fatherPtr)
	{
		return (BSTreeItr) &_tree->m_root;
	}

	return InsertNode(_tree, fatherPtr, _item, _tree->m_lessThan);
}
/****************************************************/
BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	BSTreeItr itr;

	if(NULL == _tree)
	{
		return NULL;
	}
	itr = (BSTreeItr)&_tree->m_root;
	while((BSTreeItr)((Node*) itr)->m_left != NULL)
	{
		itr = (BSTreeItr)((Node*) itr)->m_left;
	}
	return itr;

}
/****************************************************/
BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(NULL == _tree)
	{
		return NULL;
	}

	return (BSTreeItr) &_tree->m_root;
}
/****************************************************/
int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return _a == _b;
}
/****************************************************/
BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* node = NULL;
	if (NULL == _it)
	{
		return NULL;
	}
	node = (Node*)_it;
	/*to get the next node we go right and then left to the end of the tree.*/
	if(node->m_right != NULL)
	{
		node = node->m_right;
		while(node->m_left != NULL)
		{
			node = node->m_left;
		}

		return (BSTreeItr)node;
	}
	/*otherwise: next node is the root. going up in the tree until we meet the root*/
	while(node->m_father->m_right == node)
	{
		node = node->m_father;
	}

	return (BSTreeItr)node->m_father;
}
/****************************************************/
BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* node = NULL;
		if (NULL == _it)
		{
			return NULL;
		}
		node = (Node*)_it;
		/*to get the prev node we go left and then right to the end of the tree.*/
		if(node->m_left != NULL)
		{
			node = node->m_left;
			while(node->m_right != NULL)
			{
				node = node->m_right;
			}

			return (BSTreeItr)node;
		}
		/*otherwise: prev node is the root. going up in the tree until we meet the root*/
		/*check if Begin*/
		while(node->m_father->m_left == node)
		{
			node = node->m_father;
			/*if(node->m_father == node)*/
		}

		return (BSTreeItr)node->m_father;
	}
/****************************************************/
void* BSTreeItr_Remove(BSTreeItr _it)
{
	BSTreeItr nextItr;
	if(NULL == _it)
	{
		return NULL;
	}
	if(IsLeaf((Node*)_it))
	{
		return RemoveLeaf((Node*)_it);
	}
	if(OnlyOneChild((Node*)_it))
	{
		RemoveNodeWithOneChild((Node*)_it);
	}
	nextItr = BSTreeItr_Next(_it);
	SwapNodesData(((Node*)_it), (Node*)nextItr);

	return RemoveNodeWithOneChild((Node*) nextItr);
}
/****************************************************/
void* BSTreeItr_Get(BSTreeItr _it)
{
	if(NULL == _it)
	{
		return NULL;
	} 
	/*itterator is at end of the tree*/
	else if ((NULL == ((Node*)_it)->m_right) && (NULL == ((Node*)_it)->m_left))
	{
		return NULL;
	}
	
	return ((Node*) _it)->m_data;
}
/******************************************************/
BSTreeItr BSTree_ForEach(const BSTree* _tree, BSTreeTraversalMode _mode, ActionFunction _action, void* _context)
{
	BSTreeItr itr;
	if(NULL == _tree || NULL == _action)
	{
		return NULL;
	}
	if(NULL == _tree->m_root.m_left)
	{
		return (BSTreeItr)&_tree->m_root;
	}
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
			itr = BSTree_ForEach_PREORDER(_tree->m_root.m_left, _action, _context);
			return (NULL == itr) ? (BSTreeItr)&_tree->m_root : itr;

		case BSTREE_TRAVERSAL_INORDER:
			itr = BSTREE_ForEach_INORDER(_tree->m_root.m_left, _action, _context);
			return (NULL == itr) ? (BSTreeItr)&_tree->m_root : itr;

		case BSTREE_TRAVERSAL_POSTORDER:
			itr = BSTREE_ForEach_POSTORDER(_tree->m_root.m_left, _action, _context);
			return (NULL == itr) ? (BSTreeItr)&_tree->m_root : itr;

		default :
			return NULL;
	}
}
/******************************************************/
/******************************************************/
/*******************Inner Functions********************/
/******************************************************/
static Node* CreateNode(void* _item)
{
	Node* newNode = (Node*) malloc(sizeof(Node));
	if(!newNode)
	{
		return NULL;
	}
	newNode->m_data = _item;
	newNode->m_father = NULL;
	newNode->m_left = NULL;
	newNode->m_right = NULL;

	return newNode;
}
/****************************************************/
static void DestroyTreeRec(Node* _root, void (*_destroyer)(void*))
{
	if(NULL == _root)
	{
		return;
	}

	DestroyTreeRec(_root->m_left, _destroyer);
	DestroyTreeRec(_root->m_right, _destroyer);

	/*_root->m_left = NULL;
	_root->m_right = NULL;
	_root->m_father = NULL;*/

	if(_destroyer != NULL)
	{
		_destroyer(_root->m_data);
	}

	free(_root);
}
/****************************************************/
static Node* FindFatherOfNode(Node* _node, void* _item, LessComparator _less)
{
	if(_less(_item, _node->m_data))
	{
		if(NULL == _node->m_left)
		{
			return _node;
		}

		return FindFatherOfNode(_node->m_left, _item, _less);
	}

	if(_less(_node->m_data, _item))
	{
		if(NULL == _node->m_right)
		{
			return _node;
		}

		return FindFatherOfNode(_node->m_right, _item, _less);
	}
	
	return NULL;
}

/****************************************************/
static BSTreeItr InsertNode(BSTree*_tree, Node* _father,void* _item, LessComparator _less)
{
	Node* newNode = CreateNode(_item);
	if(NULL == newNode)
	{
		return (BSTreeItr)&_tree->m_root;
	}
	newNode->m_father = _father;
	if(_less(_item, _father->m_data))
	{
		_father->m_left = newNode;
	}
	else
	{
		_father->m_right = newNode;
	}

	return (BSTreeItr)newNode;
}
/****************************************************/
static int IsLeaf(Node* _node)
{
	if(_node->m_left == NULL  &&  _node->m_right == NULL)
	{
		return 1;
	}

	return 0;
}
/****************************************************/
static void* RemoveLeaf(Node* _node)
{
	void* removeData = _node->m_data;

	/*_node->m_data = NULL;
	_node->m_left = NULL;
	_node->m_right = NULL;*/

	if(_node->m_father->m_left == _node)
	{
		_node->m_father->m_left = NULL;
	}

	else
	{
		_node->m_father->m_right = NULL;
	}

	/*_node->m_father = NULL;*/

	free(_node);

	return removeData;
}
/****************************************************/
static int OnlyOneChild(Node* _node)
{
	if((_node->m_left != NULL) && (NULL == _node->m_right))
	{
		return 1;
	}
	else if((NULL == _node->m_left) && (_node->m_right != NULL))
	{
		return 1;
	}

	return 0;
}
/****************************************************/
static void* RemoveNodeWithOneChild(Node* _node)
{
	if(_node->m_left)
	{
		if(_node->m_father->m_left == _node)
		{
			_node->m_father->m_left = _node->m_left;
		}

		else
		{
			_node->m_father->m_right = _node->m_left;
		}
	}	

	else if(_node->m_right)
	{
		if(_node->m_father->m_left == _node)
		{
			_node->m_father->m_left = _node->m_right;
		}

		else
		{
			_node->m_father->m_right = _node->m_right;
		}
	}
	/*free leaf instead*/
	return RemoveLeaf(_node);
}
/****************************************************/
static void SwapNodesData(Node* _n1, Node* _n2)
{
	void* temp = _n1->m_data;

	_n1->m_data = _n2->m_data;

	_n2->m_data = temp;
}

/****************************************************/
static BSTreeItr BSTree_ForEach_PREORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr itr;
	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr)_node;
	}
	if(_node->m_left != NULL)
	{
		itr = BSTree_ForEach_PREORDER(_node->m_left, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}
	if(_node->m_right != NULL)
	{
		itr = BSTree_ForEach_PREORDER(_node->m_right, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}

	return NULL;
}
/****************************************************/
static BSTreeItr BSTree_ForEach_INORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr itr;
	if(_node->m_left != NULL)
	{
		itr = BSTree_ForEach_INORDER(_node->m_left, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}
	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr)_node;
	}
	if(_node->m_right != NULL)
	{
		itr = BSTree_ForEach_INORDER(_node->m_right, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}

	return NULL;
}
/****************************************************/
static BSTreeItr BSTree_ForEach_POSTORDER(Node* _node, ActionFunction _action, void* _context)
{
	BSTreeItr itr;
	if(_node->m_left != NULL)
	{
		itr = BSTree_ForEach_POSTORDER(_node->m_left, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}
	if(_node->m_right != NULL)
	{
		itr = BSTree_ForEach_POSTORDER(_node->m_right, _action, _context);
		if(itr != NULL)
		{
			return itr;
		}
	}
	if(_action(_node, _context) == 0)
	{
		return (BSTreeItr)_node;
	}

	return NULL;
}
/****************************************************/
/*
void TreePrint(BSTree* _tree, BSTreeTraversalMode _traverseMode)
{
	if(NULL == _tree)
	{
		printf("Tree is NULL");
	}
	switch(_traverseMode)
	{
		case BSTREE_TRAVERSAL_PREORDER:
		printf("%d\n", *(int*)_tree->m_root.m_data);
		TreePrint((BSTree*)_tree->m_root.m_left,BSTREE_TRAVERSAL_PREORDER);
		TreePrint((BSTree*)_tree->m_root.m_right,BSTREE_TRAVERSAL_PREORDER);
		break;
		
		case BSTREE_TRAVERSAL_INORDER:
		TreePrint((BSTree*)_tree->m_root.m_left,BSTREE_TRAVERSAL_INORDER);
		printf("%d\n", *(int*)_tree->m_root.m_data);
		TreePrint((BSTree*)_tree->m_root.m_left,BSTREE_TRAVERSAL_PREORDER);
		break;
		
		case BSTREE_TRAVERSAL_POSTORDER:
		TreePrint((BSTree*)_tree->m_root.m_left,BSTREE_TRAVERSAL_POSTORDER);
		TreePrint((BSTree*)_tree->m_root.m_right,BSTREE_TRAVERSAL_POSTORDER);
		printf("%d\n", *(int*)_tree->m_root.m_data);
		break;
	}
}

*/
