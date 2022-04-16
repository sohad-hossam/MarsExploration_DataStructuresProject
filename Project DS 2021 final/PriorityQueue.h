#pragma once
#include <iostream>

using namespace std;

template < typename T>
class node
{
private:
	T Item;
	node<T>* Next;
	int priority;
public:
	node();
	node(const T& item);
	node(const T& item, int p);
	node(const T& item, node<T>* next, int p);
	void setItem(const T& item);
	void setNext(node<T>* next);
	T getItem() const;
	node<T>* getNext() const;
	int getpriority();
};
template < typename T>
node<T>::node()
{
	next = nullptr;
}

template < typename T>
node<T>::node(const T& item)
{
	Item = item;
	Next = nullptr;
}

template < typename T>
node<T>::node(const T& item, int p)
{
	Item = item;
	Next = nullptr;
	priority = p;
}
template < typename T>
node<T>::node(const T& item, node<T>* next, int p)
{
	Item = item;
	Next = next;
	priority = p;
}
template < typename T>
void node<T>::setItem(const T& item)
{
	Item = item;
}

template < typename T>
void node<T>::setNext(node<T>* next)
{
	Next = next;
}

template < typename T>
T node<T>::getItem() const
{
	return Item;
}

template < typename T>
node<T>* node<T>::getNext() const
{
	return Next;
}

template<typename T>
inline int node<T>::getpriority()
{
	return priority;
}



template <typename T>
class PriorityQueue
{
private:

	node<T>* Front;
	node<T>* Back;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool insert(const T& item, int priority);
	bool dequeue(T& item);
	bool peek(T& item)  const;
	~PriorityQueue();

	PriorityQueue(const PriorityQueue<T>& L);
};


template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	Front = nullptr;
	Back = nullptr;

}


template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (Front == nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool PriorityQueue<T>::insert(const T& item, int priority)
{
	node<T>* start = Front;

	node<T>* temp = new node<T>(item, priority);

	if (isEmpty())
	{
		Front = temp;
	}
	else
	{
		if (Front->getpriority() > priority)
		{

			temp->setNext(Front);
			Front = temp;
		}
		else
		{

			while (start->getNext() != NULL &&
				start->getNext()->getpriority() < priority)
			{
				start = start->getNext();
			}
			temp->setNext(start->getNext());
			start->setNext(temp);
		}
	}
	return true;
}


template <typename T>
bool PriorityQueue<T>::dequeue(T& item)
{
	if (isEmpty())
		return false;

	node<T>* deleted = Front;
	item = Front->getItem();
	Front = Front->getNext();
	if (deleted == Back)
		Back = nullptr;


	delete deleted;

	return true;


}


template <typename T>
bool PriorityQueue<T>::peek(T& item) const
{
	if (isEmpty())
		return false;

	item = Front->getItem();
	return true;

}


template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
	T deleted;
	while (dequeue(deleted));
}


template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& L)
{
	node<T>* newnode = L.Front;
	if (!newnode) 
	{
		Front = nullptr;
		Back = nullptr;
		return;
	}

	node<T>* NewNode = new node<T>(newnode->getItem());//ptr
	Front = NewNode;
	Back = NewNode;
	newnode = newnode->getNext();
	while (newnode)
	{
		node<T>* Newnode = new node<T>(newnode->getItem());//ptr
		Back->setNext(Newnode);
		Back = Newnode;
		newnode = newnode->getNext();
	}
}

