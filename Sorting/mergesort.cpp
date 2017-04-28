#include "util.h"
using namespace std;
namespace NP_MERGESORT {
	
	void printArray(A ** array, int size) {
		for (int index = 0; index < size; index++) {
			array[index]->print();
		}

		cout << "\n";
	}

	void merge(A ** array, int startIndex, int mid, int endIndex, int len) {
		A ** temp = new A * [len];
		
		int leftCursor = startIndex;
		int rightCursor = endIndex;
		int bookmark = mid + 1;
		int cursor = leftCursor;

		while (leftCursor <= mid && bookmark <= rightCursor) {
			if (*array[leftCursor] <= *array[bookmark])
				temp[cursor++] = array[leftCursor++];
			else
				temp[cursor++] = array[bookmark++];
		}

		while (leftCursor <= mid)
			temp[cursor++] = array[leftCursor++];
		
		while (bookmark <= rightCursor)
			temp[cursor++] = array[bookmark++];
		

		for (int index = startIndex; index <= endIndex; index++)
			array[index] = temp[index];
		

		cout << "After pass: ";
		printArray(array, len);
	}
	void mergesort(A ** array, int start, int end, int len) {
		if (start < end) {
			int mid = (start + end) / 2;
			mergesort(array, start, mid, len);
			mergesort(array, mid + 1, end, len);
			merge(array, start, mid, end, len);
		}
	}
	
}

using namespace NP_MERGESORT;

int main() {
	const int len = 7;
	A * array[len] = { &B(9), &B(4), &B(8), &B(3), &B(5), &B(2), &B(1) };
	cout << "Initial Array" << ": ";
	printArray(array, len);
	cout << "\n";
	mergesort(array, 0, len - 1, len);
	return 0;
}