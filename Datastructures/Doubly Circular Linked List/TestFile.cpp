#include "LinkedList.h"
#include <iostream>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	LinkedList<int> testQueue;

	for (int i = 0; i < 10; i++)
	{
		testQueue.enqueue(i);
	}

	std::cout << "Peek gives us: " << testQueue.peek() << "\n";
	std::cin.get();
	std::cout << "\n";

	for (int i = 0; i < 5; i++)
	{
		std::cout << "dequeue[" << i + 1 << "]: \t" << testQueue.dequeue() << "\n";
	}
	std::cout << "\n";
	std::cin.get();


	std::cout << "Peek gives us: " << testQueue.peek() << "\n";
	std::cin.get();
	std::cout << "\n";

	for (int i = 0; i < 4; i++)
	{
		std::cout << "dequeue[" << i + 1 << "]: \t" << testQueue.dequeue() << "\n";
	}
	std::cout << "\n";
	std::cin.get();

	std::cout << "Peek gives us: " << testQueue.peek() << "\n";
	std::cout << "isEmpty() gives us: " << testQueue.isEmpty() << "\n";
	std::cin.get();
	std::cout << "\n";

	try
	{
		for (int i = 0; i < 100; i++)
		{
			testQueue.dequeue();
		}
	}
	catch (char *e)
	{
		std::cout << e << "\n";
	}
	std::cin.get();
	
	for (int i = 0; i < 5; i++)
	{
		testQueue.enqueue(i);
	}
	

	return 0;
}