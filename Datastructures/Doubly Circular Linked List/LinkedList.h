#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "..\..\ADT\ADT\IQueue.h"

template <typename T>
class LinkedList : public IQueue<T>
{
	private:
		class Node
		{
			public:
				Node* next;
				T element;
				Node(T element, Node* next = nullptr) { this->element = element; this->next = nullptr; }
		};
		Node *first;
		Node *last;


	public:
		LinkedList();
		~LinkedList();
		void enqueue(const T& element);
		T dequeue();
		T peek() const;
		bool isEmpty() const;

};
#endif // !LINKEDLIST_H

template<typename T>
inline LinkedList<T>::LinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	if (this->first == this->last || !this->first) // check if only 1 element
	{
		delete this->first;
	}
	else
	{
		Node* toRemove = this->first;
		Node* walker = this->first->next;
		while (walker != nullptr) // while it's not nullptr
		{
			delete toRemove;
			toRemove = walker;
			walker = walker->next;
		}
		delete toRemove;
	}

}

template<typename T>
inline void LinkedList<T>::enqueue(const T & element)
{
	Node* newNode = new Node(element);
	if (!this->first) //check if nullptr
	{
		this->first = newNode;
		this->last = newNode;
	}
	else
	{
		this->last->next = newNode;
		this->last = newNode;
	}
	

}

template<typename T>
inline T LinkedList<T>::dequeue()
{
	if (!this->first) //check if nullptr
	{
		throw "No elements in queue!";
	}
	else
	{
		T returnElement = this->first->element;
		Node* toRemove = this->first;
		if (this->first->next == nullptr)
		{
			this->first = nullptr;
		}
		else
		{
			this->first = this->first->next;
		}
		delete toRemove;
		return returnElement;
	}
}

template<typename T>
inline T LinkedList<T>::peek() const
{
	if (!this->first) //check if nullptr
	{
		throw "No elements in queue!";
	}
	else
	{
		T returnElement = this->first->element;
		return returnElement;
	}
}

template<typename T>
inline bool LinkedList<T>::isEmpty() const
{
	return (!this->first);
}
