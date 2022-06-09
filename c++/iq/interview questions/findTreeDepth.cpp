#include <cstdio>

typedef struct Node{
    int m_data;
    Node* m_left;
    Node* m_right;
}Node;

int treeDepth(Node* a_node)
{
    if(a_node == NULL)
    {
        return -1;
    }
    int lDepth = treeDepth(a_node->m_left);
    int rDepth = treeDepth(a_node->m_left);
    return (lDepth > rDepth) ? lDepth + 1 : rDepth + 1;
}

Node* createNode(int a_data)
{
    Node* temp = new Node();
    temp->m_left = temp->m_right = NULL;
    temp->m_data = a_data;

    return temp;
}

int main(int argc, char** argv)
{
    Node* node = createNode(1);
    node->m_left = createNode(2);
    node->m_right = createNode(3);
    node->m_left->m_left = createNode(4);
    node->m_left->m_right = createNode(5);

    int depth = treeDepth(node);
    printf("tree depth is: %d", depth);
}
