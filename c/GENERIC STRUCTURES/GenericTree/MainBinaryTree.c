#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

int main(void)
{
	Tree* ptrTree;	
	int traverseModePreOrder = 0;
	int traverseModeInOrder = 0;
	int traverseModePostOrder = 0;
	TreeCreate();
	/*Insert nodes*/
	TreeInsert(ptrTree, 9);
	TreeInsert(ptrTree, 4);
	TreeInsert(ptrTree, 15);
	TreeInsert(ptrTree, 6);
	TreeInsert(ptrTree, 12);
	TreeInsert(ptrTree, 17);
	TreeInsert(ptrTree, 2);
	/*Insert nodes*/
	printf("Pre Order Display");
	TreePrint(ptrTree, traverseModePreOrder);
	printf("In Order Display");
	TreePrint(ptrTree, traverseModeInOrder);
	printf("Post Order Display");
	TreePrint(ptrTree, traverseModePostOrder);
	temp = TreeIsDataFound(ptrTree, 4);
	if(temp)
	{
		printf("Data node = %d found!", ptrTree->m_root->m_data);
	}
	else
	{
		printf("Data not found in tree\n");
	}
	TreeDestroy(ptrTree);
	
	return 0;
}
