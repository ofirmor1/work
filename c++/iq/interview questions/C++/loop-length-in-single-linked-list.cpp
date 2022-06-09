#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef struct Node{
    int data;
    Node* next;
}Node;

Node* newNode(int data)
{
    Node* node = new Node;
    node->data = data;
    node->next = NULL;

    return node;
}

int loopLength(Node* head)
{
    if(!head || !head->next)
    {
        return -1;
    }

    Node* slow = head, *fast = head;

    while(slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
        {
            Node*  temp = slow;
            temp = temp->next;
            int  count = 1;
            while(temp != slow)
            {
                temp = temp->next;
                ++count;
            }

            return count;
        }
    }
    return -1;
}

int main() { 
	cout<<"linked list is built like the example\n";
	cout<<"1->2->3->4->5->6->7->8->3->4->....\n";
	Node *head = newNode(1); 
	head->next = newNode(2); 
	head->next->next = newNode(3); 
	head->next->next->next = newNode(4); 
	head->next->next->next->next = newNode(5);
	head->next->next->next->next->next = newNode(6);
	head->next->next->next->next->next->next = newNode(7);
	head->next->next->next->next->next->next->next = newNode(8);

	/* Create the loop  */
	//the next pinter of node having value 8 coonected to node having value 3
	head->next->next->next->next->next->next->next->next = head->next->next ; 

	printf("loop length: %d \n", loopLength(head)); 

	return 0; 
} 
