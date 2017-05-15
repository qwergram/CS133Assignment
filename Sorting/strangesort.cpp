// quicksort
#include "util.h"
using namespace std;

int len;

namespace NP_STRANGESORT {

	void printArray(A ** array, int size) {
		for (int index = 0; index < size; index++) {
			array[index]->print();
		}

		cout << "\n";
	}

	void indexSwap(A ** array, int index1, int index2) {
		A * tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}

	void SortFirstMiddleLast(A ** array,
		int loIndex, int midIndex,
		int hiIndex
	)
	{
		A * low = array[loIndex];
		A * mid = array[midIndex];
		A * hi = array[hiIndex];

		while ((*low > *mid) || (*mid > *hi)) {
			if (*low > *mid)
				indexSwap(array, loIndex, midIndex);
			else if (*mid > *hi)
				indexSwap(array, midIndex, hiIndex);
			else if (*low > *hi)
				indexSwap(array, loIndex, hiIndex);
			low = array[loIndex];
			mid = array[midIndex];
			hi = array[hiIndex];
		}
	}

	int partition(A ** array, int fromIndex, int toIndex) {
		
		int smallIndex = fromIndex - 1;
		
		A* pivot = array[toIndex];
		
		for (int k = fromIndex; k < toIndex; k++) {
			if (*array[k] <= *pivot) {
				smallIndex++;
				indexSwap(array, k, smallIndex);
			}
		}

		indexSwap(array, toIndex, smallIndex + 1);
		cout << "Pivot = " << array[smallIndex + 1]->method() << "\n";
		printArray(array, len);
		return smallIndex + 1;
	}

	void insertionSort(A ** array, int fromIndex, int toIndex)
	{
		for (int cursor = fromIndex; cursor < toIndex; cursor++) {
			int secondCursor = cursor - 1;
			A * temp = array[cursor];

			while (secondCursor >= 0 && *temp < *array[secondCursor]) {
				*array[secondCursor + 1] = *array[secondCursor];
				secondCursor--;
			}

			*array[secondCursor + 1] = *temp;
		}
	}

	void strangeSort(A ** arr, int fromIndex, int toIndex) {
		if (fromIndex + 4 < toIndex) {
			SortFirstMiddleLast(arr, fromIndex, (fromIndex + toIndex) / 2, toIndex);
			int position = partition(arr, fromIndex, toIndex);
			strangeSort(arr, fromIndex, position - 1);
			strangeSort(arr, position + 1, toIndex);
		}
		else if (fromIndex < toIndex) {
			insertionSort(arr, fromIndex, toIndex);
		}
	}


}

using namespace NP_STRANGESORT;

int main() {
	len = 10;
	A ** arr = new A*[len] { &B(9), &B(1), &B(2), &B(7), &B(5), &B(4), &B(8), &B(3), &B(6), &B(0) };
	cout << "Initial Array : ";
	printArray(arr, len);
	strangeSort(arr, 0, len - 1);
	cout << "Sorted Array : ";
	printArray(arr, len);
	cin.get();
	return 0;
}