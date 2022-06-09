#include "genericBST.h"
#include <stdlib.h>
#include <stdio.h>
#include "genericBST.h"

int LessComp(void* _left, void* _right)
{
	return *(int*)_left < *(int*)_right;
}

int PrintElement(void* _element, void* _context)
{
	printf("%d ",*(int*)_element);
	return 1;
}

void PrintTree(BSTree* _tree)
{
	BSTree_ForEach(_tree, BSTREE_TRAVERSAL_INORDER, PrintElement, NULL);
}

BSTree* createTree()
{
	int index;
	int arrSize;
	BSTree* tree;
	int arr[] = {10,20,8,12,6,4,5,14,25,21,30};
	arrSize = sizeof(arr)/sizeof(arr[0]);
	tree = BSTree_Create(LessComp);
	for(index = 0; index < arrSize; index++)
	{
		BSTree_Insert(tree, &arr[index]);
	}
	PrintTree(tree);
	return tree;
}

int main(void)
{
	createTree();
}
/*
UNIT(Tree_Create_ok)
	BSTree* tree = BSTree_Create(LessTreeComp);
	ASSERT_THAT( BSTree_Create(NULL) == NULL);
	ASSERT_THAT( tree != NULL);
	BSTree_Destroy(&tree,NULL);
	BSTree_Destroy(&tree,NULL);
	BSTree_Destroy(NULL,NULL);
END_UNIT

UNIT(Tree_Create_and_fill)
	BSTree* tree = createAndFillTree();
	ASSERT_THAT( tree != NULL);

	BSTree_Destroy(NULL,NULL);
END_UNIT

TEST_SUITE(Test Tree)
	TEST(Tree_Create_ok)
	TEST(Tree_Create_and_fill)
END_SUITE

*/
