//Insertion sort
#include "util.h"
using namespace std;

namespace NP_INSERTIONSORT {

	void printArray(A ** array, int size) {
		for (int index = 0; index < size; index++) {
			array[index]->print();
		}

		cout << "\n";
	}

	void insertionsort(A ** array, int fromIndex, int toIndex) {
		if (fromIndex < 1)
			fromIndex = 1;

		for (int outerIndex = fromIndex; outerIndex < toIndex; outerIndex++) {
			int innerIndex = outerIndex - 1;
			A * temp = array[outerIndex];

			while (innerIndex >= 0 && *temp < *array[innerIndex]) {
				array[innerIndex + 1] = array[innerIndex];
				innerIndex--;
			}

			array[innerIndex + 1] = temp;
			cout << "After pass " << outerIndex << "  : ";
			//Printing array after pass
			printArray(array, toIndex);
		}
	}
	int main() {
		int size = 9;
		A ** array = nullptr;
		array = new A*[size] { &B(1), &B(7), &B(3), &B(0), &B(3), &B(1), &B(9), &B(9), &B(7) };
		cout << "Initial Array : ";
		printArray(array, size);
		insertionsort(array, 0, size);
		return 0;
	}
}