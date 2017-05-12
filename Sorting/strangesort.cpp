// #include "util.h"
#include <iostream>

using namespace std;

namespace NP_STRANGESORT {
	
	void printArray(int*, int);
	void strangeSort(int *, int, int);
	int partition(int *, int, int);
	void indexSwap(int *, int, int);
	void SortFirstMiddleLast(int *, int, int, int);

	void printArray(int * array, int size) {
		for (int index = 0; index < size; index++) {
			cout << array[index] << ' ';
		}

		cout << "\n";
	}

	void strangeSort(int * arr, int fromIndex, int toIndex) 
	{
		if (fromIndex < toIndex) {
			int position = partition(arr, fromIndex, toIndex);
			strangeSort(arr, fromIndex, position - 1);
			strangeSort(arr, position + 1, toIndex);
		}
	}

	int partition(int * array, int fromIndex, int toIndex)
	{
		int pivotIndex = (fromIndex + toIndex) / 2;
		SortFirstMiddleLast(array, fromIndex, pivotIndex, toIndex);

		int pivot = array[pivotIndex];
		indexSwap(array, pivotIndex, toIndex - 1);

		int frontIndex = fromIndex + 1;
		int backIndex = pivotIndex - 1;

		while (frontIndex < backIndex) {
			while (frontIndex < backIndex && pivot >= array[frontIndex])
				frontIndex++;

			while (frontIndex < backIndex && array[backIndex] >= pivot)
				backIndex--;

			indexSwap(array, frontIndex++, pivotIndex--);
		}
		indexSwap(array, fromIndex, frontIndex);
		return frontIndex;
	}

	void indexSwap(int * array, int index1, int index2) 
	{
		int tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}

	void SortFirstMiddleLast(int * array,
		int loIndex, int midIndex,
		int hiIndex) 
	{
		int low = array[loIndex];
		int mid = array[midIndex];
		int hi = array[hiIndex];
		while ((low > mid) || (mid > hi)) {
			if (low > mid)
				indexSwap(array, loIndex, midIndex);
			if (mid > hi)
				indexSwap(array, midIndex, hiIndex);
			if (low > hi)
				indexSwap(array, loIndex, hiIndex);
			low = array[loIndex];
			mid = array[midIndex];
			hi = array[hiIndex];
		}
	}
}

int main() {
	const int ARRAY_SIZE = 8;
	int intArray[8] = { -6, -3, 8, -9, -2, 5, 1, -4 };
	int* intPtr = nullptr;

	cout << "The original array: " << endl;
	NP_STRANGESORT::printArray(intArray, ARRAY_SIZE);
	cout << endl;

	NP_STRANGESORT::strangeSort(intArray, 0, ARRAY_SIZE);

	cout << "The array after quicksort:" << endl;
	NP_STRANGESORT::printArray(intArray, ARRAY_SIZE);

	cin.get();
	return EXIT_SUCCESS;
}