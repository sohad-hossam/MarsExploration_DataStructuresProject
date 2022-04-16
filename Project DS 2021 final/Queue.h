#pragma once
#include <iostream>

using namespace std;

template < typename T>
class Node
{
private:
	T Item;
	Node<T>* Next;
public:
	Node();
	Node(const T& item);
	Node(const T& item, Node<T>* next);
	void setItem(const T& item);
	void setNext(Node<T>* next);
	T getItem() const;
	Node<T>* getNext() const;
};

template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& item)
{
	Item = item;
	Next = nullptr;
}

template < typename T>
Node<T>::Node(const T& item, Node<T>* next)
{
	Item = item;
	Next = next;
}
template < typename T>
void Node<T>::setItem(const T& item)
{
	Item = item;
}

template < typename T>
void Node<T>::setNext(Node<T>* next)
{
	Next = next;
}

template < typename T>
T Node<T>::getItem() const
{
	return Item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return Next;
}


template <typename T>
class Queue
{
private:


	Node<T>* Front;
	Node<T>* Back;
public:
	Queue();
	bool isEmpty() const;
	bool enqueue(const T& item);

	bool dequeue(T& item);
	bool peek(T& item)  const;
	~Queue();


	Queue(const Queue<T>& L);
};


template <typename T>
Queue<T>::Queue()
{
	Front = nullptr;
	Back = nullptr;
}


template <typename T>
bool Queue<T>::isEmpty() const
{
	if (Front == nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool Queue<T>::enqueue(const T& item)
{
	Node<T>* newnode = new Node<T>(item);
	if (isEmpty())	
		Front = newnode; 
	else
		Back->setNext(newnode); 

	Back = newnode; 
	return true;
} 





template <typename T>
bool Queue<T>::dequeue(T& item)
{
	if (isEmpty())
		return false;

	Node<T>* deleted = Front;
	item = Front->getItem();
	Front = Front->getNext();
	if (deleted == Back)	
		Back = nullptr;

	delete deleted;

	return true;

}


template <typename T>
bool Queue<T>::peek(T& item) const
{
	if (isEmpty())
		return false;

	item = Front->getItem();
	return true;

}


template <typename T>
Queue<T>::~Queue()
{
	T Delete;

	while (dequeue(Delete));
}


template <typename T>
Queue<T>::Queue(const Queue<T>& L)
{
	Node<T>* newnode = L.Front;
	if (!newnode) 
	{
		Front = nullptr;
		Back = nullptr;
		return;
	}

	
	Node<T>* NewNode = new Node<T>(newnode->getItem());
	Front = NewNode;
	Back = NewNode;
	newnode = newnode->getNext();

	
	while (newnode)
	{
		Node<T>* Newnode = new Node<T>(newnode->getItem());
		Back->setNext(Newnode);
		Back = Newnode;
		newnode = newnode->getNext();
	}
}
