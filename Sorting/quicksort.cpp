// quicksort
#include "util.h"
using namespace std;

namespace NP_QUICKSORT {
	
	int len;

	void printArray(A ** array, int size) {
		for (int index = 0; index < size; index++) {
			array[index]->print();
		}

		cout << "\n";
	}

	void swap(A ** array, int index1, int index2) {
		A * tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}
	int partition(A ** array, int fromIndex, int toIndex) {
		A * pivot = array[toIndex];
		int small = fromIndex - 1;

		for (int k = fromIndex; k < toIndex; k++) {
			if (*array[k] <= *pivot) {
				small++;
				swap(array, k, small);
			}
		}

		swap(array, toIndex, small + 1);
		cout << "Pivot = " << (*array[small + 1]).method() << "\n";
		printArray(array, len);
		return small + 1;
	}


	void quickSort(A ** arr, int fromIndex, int toIndex) {
		if (fromIndex < toIndex) {
			int position = partition(arr, fromIndex, toIndex);
			quickSort(arr, fromIndex, position - 1);
			quickSort(arr, position + 1, toIndex);
		}
	}
	
	int main() {
		len = 7;
		A ** arr = nullptr;
		arr = new A*[len] { &B(9), &B(4), &B(8), &B(3), &B(1), &B(2), &B(5) };
		cout << "Initial Array : ";
		printArray(arr, len);
		quickSort(arr, 0, len - 1);
		return 0;
	}
}