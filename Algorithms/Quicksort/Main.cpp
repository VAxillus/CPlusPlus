#include <iostream>
#include <ctime>


void quickSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);
void swap(int &left, int &right);

int main()
{
	srand(time(NULL));
	int arr[1000];
	for (int i = 0; i < 1000; i++)
	{
		arr[i] = rand() % 800;
		std::cout << arr[i] << "\t";
	}
	std::cout << "\n\nEnter any key to sort the list!";
	std::cin.get();

	quickSort(arr, 0, 999);

	for (int i = 0; i < 1000; i++)
	{
		std::cout << arr[i] << "\t";
	}
	std::cout << "\n\n";
	(system("pause"));
	return 0;
}

void quickSort(int arr[], int start, int end)
{
	
	if (start < end)
	{
		int pivotIndex = partition(arr, start, end);
		quickSort(arr, start, pivotIndex - 1);
		quickSort(arr, pivotIndex + 1, end);
		
	}
}

int partition(int arr[], int start, int end)
{
	
	int pivotValue = arr[start];
	int pivotPosition = start;

	// partition the "subarray" from start to end
	for (int i = start + 1; i <= end; i++)
	{
		if (arr[i] < pivotValue)
		{
			swap(arr[pivotPosition + 1], arr[i]);
			swap(arr[pivotPosition], arr[pivotPosition + 1]);
			pivotPosition++;
		}

	}

	return pivotPosition;
}

void swap(int &left, int &right)
{
	int temp = left;
	left = right;
	right = temp;
}
