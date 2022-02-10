#include <iostream>
#include <stddef.h>
#include <cassert>
using std::cout;
using std::endl;

const size_t CAPACITY = 10;

class Cat{
public:
    void walk() const { std::cout << "walk the cat\n"; }
};

// Node Class
template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	Node<T>(T a_val, Node<T>* a_next): data(a_val), next(a_next){};
	Node<T>(T a_val): data(a_val), next(0) {};
};

// Queue Class
template <typename T>
class Queue
{
public:
    Queue(size_t capacity = CAPACITY);
	
    ~Queue();
	Queue(Queue const& a_queue);
	Queue& operator=(T const& a_queue);

	void enqueue(T const& a_value);
	T dequeue();

    bool isEmpty() const;
    bool isFull() const;
	void print() const;
	size_t size() const;
	size_t cap() const;

	Node<T>* getFront() const;
    Node<T>* getBack() const;

private:
    void copy(Queue const& a_queue);
	void clear();

private:
	Node<T>* front;
	Node<T>* back;
	size_t currSize;
    size_t capacity;

};

template <typename T>
Queue<T>::Queue(size_t a_capacity)
{
	front = back = 0;
	currSize = 0;
    capacity = a_capacity;
}

template <typename T>
Queue<T>::Queue(Queue const& a_queue)
{
	front = back = 0;
	copy(a_queue);
	currSize = a_queue.currSize;
}

template <typename T>
Queue<T>::~Queue()
{
	clear();
}

template <typename T>
void Queue<T>::clear()
{
	Node<T>* temp = front;
	while (front != 0)
	{
		front = temp->next;
		delete temp;
		temp = front;
	}
	currSize = 0;
	front = back = 0;
}

template <typename T>
Queue<T>& Queue<T>::operator=(T const& a_queue)
{
	if (this != &a_queue)
	{
		
        copy(a_queue);
		clear();
		currSize = a_queue.currSize;
	}

	return *this;
}

template <typename T>
void Queue<T>::copy(Queue const& a_queue)
{
	if (a_queue.front != 0)
	{
		Node<T>* temp = a_queue.front;
		while (temp != 0)
		{
			enqueue(temp->data);
			temp = temp->next;
		}
	}

	else
	{
		front = back = 0;
	}
}
 
template <typename T>
void Queue<T>::enqueue(T const& a_value)
{
	if (back == 0)
	{
		back = new Node<T>(a_value);
		front = back;
	}
	else
	{
		Node<T>* temp = new Node<T>(a_value);
		back->next = temp;
		back = temp;
	}

	++currSize;
}

template <typename T>
T Queue<T>::dequeue()
{
	assert(front);
	Node<T>* temp = front;
	T data = front->data;
	front = front->next;
	if (front == 0)
	{
		back = 0;
	}

	--currSize;
	delete temp;
	return data;
}

template <typename T>
void Queue<T>::print() const
{
	Node<T>* temp = front;

	while (temp != 0)
	{
		cout << temp->data << endl;
		temp = temp->next;
	}
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	return currSize == 0;
}

template <typename T>
bool Queue<T>::isFull() const
{
	return currSize == capacity;
}

template <typename T>
size_t Queue<T>::size() const
{
	return currSize;
}

template <typename T>
size_t Queue<T>::cap() const
{
	return capacity;
}
 
template <typename T>
Node<T>* Queue<T>::getFront() const
{
	return front;
}

template <typename T>
Node<T>* Queue<T>::getBack() const
{
	return back;
}