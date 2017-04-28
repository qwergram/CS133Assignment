//selection sort
#include "util.h"
using namespace std;

namespace NP_SELECTIONSORT {

	void printArray(A ** array, int size) {
		for (int index = 0; index < size; index++) {
			array[index]->print();
		}

		cout << "\n";
	}

	void selectionsort(A ** array, int size) {
		for (int outerIndex = 0; outerIndex < size; outerIndex++) {
			A * small = array[outerIndex];
			int position = outerIndex;

			for (int innerIndex = outerIndex + 1; innerIndex < size; innerIndex++) {
				if (*array[innerIndex] < *small) {
					small = array[innerIndex];
					position = innerIndex;
				}
			}

			A * temp = array[position];
			array[position] = array[outerIndex];
			array[outerIndex] = temp;
			cout << "After pass " << outerIndex << "  : ";
			printArray(array, size);
		}
	}


	int main() {
		const int len = 8;
		A * array[len] = { &B(10), &B(7), &B(3), &B(1), &B(9), &B(7), &B(4), &B(3) };
		cout << "Initial Array : ";
		NP_SELECTIONSORT::selectionsort(array, len);
		return 0;
	}
}