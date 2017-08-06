#ifndef DHEAP_H
#define DHEAP_H
#include "IHeap.h"

template <typename T>
class dHeap : public IHeap<T>
{
private:

	int d;
	T * arr;
	int capacity;
	int nrOf;

	void swap(T &left, T &right);
	void spinDown(int index);
	void spinUp(int index);
	void allocateMemory();
public:
	dHeap(int capacity, int d = 2);
	dHeap(const dHeap &other);
	~dHeap();

	dHeap& operator=(const dHeap &other);

	void push(const T & item);
	T pop();
	T peek() const;
	int size() const;
	int getdValue() const;
};

template<typename T>
inline void dHeap<T>::swap(T & left, T & right)
{
	T temp = left;
	left = right;
	right = temp;
}

template<typename T>
inline void dHeap<T>::spinDown(int index)
{
	//di + 1 through di + d
	int leftMostChild = (d * index + 1);
	int rightMostChild = (this->d * index + this->d);

	int minIndex = index;

	for (int i = leftMostChild + 1; i <= rightMostChild; i++)
	{
		if (leftMostChild < this->nrOf && arr[index] < arr[leftMostChild])
		{
			minIndex = leftMostChild;
		}

		if (i < this->nrOf && arr[minIndex] < arr[i])
		{
			minIndex = i;
		}

		if (minIndex != index)
		{
			this->swap(arr[index], arr[minIndex]);
			this->spinDown(minIndex);
		}
	}


}

template<typename T>
inline void dHeap<T>::spinUp(int index)
{
	int parent = ((index - 1) / this->d);

	if (arr[parent] < arr[index])
	{
		swap(arr[parent], arr[index]);
		this->spinUp(parent);
	}
}

template<typename T>
inline void dHeap<T>::allocateMemory()
{
	this->capacity += 10000;
	T* temp = new T[this->capacity];
	for (int i = 0; i < this->capacity - 10000; i++)
	{
		temp[i] = this->arr[i];
	}
	delete[] this->arr;
	this->arr = temp;
}

template <typename T>
dHeap<T>::dHeap(int capacity, int d)
{
	this->capacity = capacity;
	this->d = d;
	this->nrOf = 0;
	this->arr = new T[this->capacity];
}

template<typename T>
inline dHeap<T>::dHeap(const dHeap & other)
{
	this->d = other.d;
	this->capacity = other.capacity;
	this->nrOf = other.nrOf;
	this->arr = new T[this->capacity];

	for (int i = 0; i < this->nrOf; i++)
	{
		this->arr[i] = other.arr[i];
	}

	for (int i = this->nrOf; i < this->capacity; i++)
	{
		this->arr[i] = T();
	}

}

template <typename T>
dHeap<T>::~dHeap()
{
	delete[] this->arr;
}

template<typename T>
inline dHeap<T> & dHeap<T>::operator=(const dHeap & other)
{
	if (this != &other)
	{
		if (!this->arr)
		{
			delete[] this->arr;
		}

		this->d = other.d;
		this->capacity = other.capacity;
		this->nrOf = other.nrOf;
		this->arr = new T[this->capacity];

		for (int i = 0; i < this->nrOf; i++)
		{
			this->arr[i] = other.arr[i];
		}
		for (int i = this->nrOf; i < this->capacity; i++)
		{
			this->arr[i] = T();
		}

	}

	return *this;
}

template <typename T>
void dHeap<T>::push(const T & item)
{
	// appending last

	if (this->nrOf == this->capacity)
	{
		this->allocateMemory();
	}

	this->arr[this->nrOf] = item;
	this->spinUp(this->nrOf);
	this->nrOf++;

}

template <typename T>
T dHeap<T>::pop()
{
	if (this->nrOf == 0)
	{
		throw "Can't perform pop on an empty heap!";
	}
	else
	{
		this->nrOf--;
		T toReturn = this->arr[0];
		this->swap(this->arr[0], this->arr[this->nrOf]);
		this->spinDown(0);
		return toReturn;
	}
}

template <typename T>
T dHeap<T>::peek() const
{
	if (this->nrOf == 0)
	{
		throw "Can't perform peek on an empty heap!";
	}
	else
	{
		return this->arr[0];
	}
}

template <typename T>
int dHeap<T>::size() const
{
	return this->nrOf;
}

template <typename T>
int dHeap<T>::getdValue() const
{
	return this->d;
}

#endif
