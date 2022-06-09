#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include "ADTDefs.h"

typedef enum TreeTraverse
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
};

typedef struct Tree Tree;
typedef struct Node Node;
typedef enum TreeTraverse TreeTraverse;

Tree* TreeCreate();
void    TreeDestroy(Tree* _tree);
ADTErr  TreeInsert(Tree* _tree, int _data);
int     TreeIsDataFound(Tree* _tree, int _data);
void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);
#endif /* #ifndef __BINARYTREE_H__ */
