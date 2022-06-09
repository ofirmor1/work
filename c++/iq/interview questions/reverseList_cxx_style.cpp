#include <iostream>
#include <list>

typedef struct Node{
    Node* m_next;
    int m_data;
    Node(int a_data)
    {
        m_data = a_data;
        m_next = NULL;
    }
}Node;

typedef struct List{
    Node* m_head;
    List()
    {
        m_head = NULL;
    }

    Node* reverseList(Node* a_node)
{
    if(!a_node)
    {
        return NULL;
    }

    if(!a_node->m_next)
    {
        m_head = a_node;
        return a_node;
    }

    Node* temp = reverseList(a_node->m_next);
    temp->m_next = a_node;
    a_node->m_next = NULL;
    return a_node;  
}

void printList()
{
    Node* temp = m_head;
    while(temp)
    {
        std::cout << temp->m_data <<std::endl;
        temp = temp->m_next;
    }
}

void push(int a_data)
{
    Node* temp = new Node(a_data);
    temp->m_next = m_head;
    m_head = temp;
}

}List;


// void reverseList(std::list<int> a_list)
// {
//     reverseList(a_list)
    
// }
int main()
{
    List ll;
    ll.push(1);
    ll.push(3);
    ll.push(5);
    ll.push(2);
    ll.push(4);

    std::cout << "before reverse" << '\n';

    ll.printList();

    ll.reverseList(ll.m_head);

    std::cout << "after reverse" << '\n';
    ll.printList();
}