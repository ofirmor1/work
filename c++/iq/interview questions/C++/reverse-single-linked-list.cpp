#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

Node* reverse(Node* node)
{
    if(!node)
    {
        return NULL;
    }

    if(!node->next)
    {
        node = head;
        return node;
    }
    Node* node1 = reverse(node->next);
    node1->next = node;
    node->next = NULL;

    return node;
}
