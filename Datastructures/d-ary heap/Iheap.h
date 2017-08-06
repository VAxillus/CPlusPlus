#ifndef IHEAP_H
#define IHEAP_H

template <typename T>
class IHeap
{
public:
	virtual ~IHeap() {};
	/* Adds the item in the heap */
	virtual void push(const T & item) = 0;
	/* Removes the "top" item from the heap */
	virtual T pop() = 0;
	/* Returns a copy of the "top" item */
	virtual T peek() const = 0;
	/* Returns the number of items in the heap */
	virtual int size() const = 0;
	/* Returns the d-value */
	virtual int getdValue() const = 0;
};
#endif // !IHEAP_H
