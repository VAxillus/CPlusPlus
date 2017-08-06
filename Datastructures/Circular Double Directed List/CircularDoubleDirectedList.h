#ifndef CIRCULARDOUBLEDIRECTEDLIST_H
#define CIRCULARDOUBLEDIRECTEDLIST_H
#include "ICircularDoubleDirectedList.h"



template <typename T>
class CircularDoubleDirectedList : public ICircularDoubleDirectedList<T>
{
	private:
		class Node
		{
			public:
				Node* left;
				Node* right;
				T element;
				Node(T element, Node* left = nullptr, Node* right = nullptr) { this->element = element; this->left = left; this->right = right; }
				~Node() {};
		};

		Node* hook;
		int nrOfElements;

		
		direction currentDirection;

		void deAllocate();
	

	public:
		
		CircularDoubleDirectedList();
		~CircularDoubleDirectedList();
		CircularDoubleDirectedList(const CircularDoubleDirectedList &other);
		CircularDoubleDirectedList& operator=(const CircularDoubleDirectedList &other);
		
		
		void addAtCurrent(const T& element);
		T& getElementAtCurrent() const;
		void removeAtCurrent();
		int size() const;
		void changeDirection();
		void moveCurrent();
		direction getCurrentDirection() const;
};

#endif // !CIRCULARDOUBLEDIRECTEDLIST_H

template<typename T>
inline void CircularDoubleDirectedList<T>::deAllocate()
{
	if (this->hook != nullptr)
	{
		this->currentDirection = FORWARD;

		for (int i = 0; i < this->nrOfElements; i++)
		{
			Node* toRemove = this->hook;
			this->hook = toRemove->right;
			this->hook->left = toRemove->left;
			toRemove->left->right = this->hook;

			delete toRemove;
			toRemove = nullptr;
		}
	}
}


template<typename T>
inline CircularDoubleDirectedList<T>::CircularDoubleDirectedList()
{
	this->hook = nullptr;
	this->nrOfElements = 0;
	this->currentDirection = FORWARD;
}

template<typename T>
inline CircularDoubleDirectedList<T>::~CircularDoubleDirectedList()
{
	this->deAllocate();
}

template<typename T>
inline CircularDoubleDirectedList<T>::CircularDoubleDirectedList(const CircularDoubleDirectedList & other)
{
	this->hook = nullptr;
	this->nrOfElements = 0;
	if (other.hook != nullptr)
	{
		this->currentDirection = FORWARD;
		
		this->addAtCurrent(other.hook->element);
		Node* start = other.hook;
		Node* otherWalker = other.hook->right;
		for (int i = 0; i < other.nrOfElements - 1 && (otherWalker != start); i++)
		{
			this->addAtCurrent(otherWalker->element);
			otherWalker = otherWalker->right;
		}
	
		this->hook = this->hook->right;
		
	}

	this->currentDirection = other.currentDirection;
}

template<typename T>
inline CircularDoubleDirectedList<T>& CircularDoubleDirectedList<T>::operator=(const CircularDoubleDirectedList & other)
{
	if (this != &other)
	{
		if (this->hook != nullptr)
		{
			this->deAllocate();
		}

		this->currentDirection = FORWARD;
		this->hook = nullptr;
		this->nrOfElements = 0;

		if (other.hook != nullptr)
		{
			this->addAtCurrent(other.hook->element);
			Node* start = other.hook;
			Node* otherWalker = other.hook->right;
			for (int i = 0; i < other.nrOfElements - 1 && (otherWalker != start); i++)
			{
				this->addAtCurrent(otherWalker->element);
				otherWalker = otherWalker->right;
			}

			this->hook = this->hook->right;
			
		}

		this->currentDirection = other.currentDirection;
		
	}

	return *this;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::addAtCurrent(const T & element)
{
	if (this->hook == nullptr)
	{
		this->hook = new Node(element);
		this->hook->left = this->hook;
		this->hook->right = this->hook;
		
	}
	else
	{
		/*
		Node* newNode = new Node(element, hook, hook->right);
		this->hook->right->left = newNode;
		this->hook->right = newNode;
		this->hook = newNode;
		*/

		this->hook = this->hook->right = this->hook->right->left = new Node(element, this->hook, this->hook->right);

	}

	this->nrOfElements++;
}

template<typename T>
inline T & CircularDoubleDirectedList<T>::getElementAtCurrent() const
{
	if (this->hook == nullptr)
	{
		throw "Exception: call of getElementAtCurrent on empty list!";
	}
	
	return this->hook->element;
	
}

template<typename T>
inline void CircularDoubleDirectedList<T>::removeAtCurrent()
{
	if (this->hook == nullptr)
	{
		throw "Exception: call of removeAtCurrent on empty list!";
	}

	Node* toRemove = this->hook;
	this->hook = toRemove->right;
	this->hook->left = toRemove->left;
	toRemove->left->right = this->hook;

	if (this->currentDirection == BACKWARD)
	{
		this->moveCurrent();
	}
		
	delete toRemove;
	toRemove = nullptr;
	this->nrOfElements--;
	if (this->nrOfElements == 0)
		this->hook = nullptr;

}

template<typename T>
inline int CircularDoubleDirectedList<T>::size() const
{
	return this->nrOfElements;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::changeDirection()
{
	this->currentDirection == FORWARD ? this->currentDirection = BACKWARD : this->currentDirection = FORWARD;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::moveCurrent()
{
	if (this->hook == nullptr)
	{
		throw "Exception: call of moveCurrent on empty list!";
	}

	this->currentDirection == FORWARD ? this->hook = hook->right : this->hook = hook->left;
	
}


template<typename T>
typename ICircularDoubleDirectedList<T>::direction CircularDoubleDirectedList<T>::getCurrentDirection() const
{
	return this->currentDirection;
	
}
