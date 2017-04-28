#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;
int len;

// Test classes w/ Inheritance like model
class Comparable {
public:
	Comparable(int num) {};
	virtual int method() = 0;
	virtual bool operator>(Comparable & lhs) = 0;
	virtual bool operator<(Comparable & lhs) = 0;
	virtual bool operator==(Comparable & lhs) = 0;
	virtual bool operator>=(Comparable & lhs) = 0;
	virtual bool operator<=(Comparable & lhs) = 0;
	virtual bool operator!=(Comparable & lhs) = 0;
	virtual void print() = 0;
};

class B : virtual public Comparable {
public:
	B(int num) : Comparable(num) { this->number = num; }
	virtual int method() { return this->number; }
	virtual bool operator>(Comparable & lhs) { return this->number < dynamic_cast<B&>(lhs).method(); };
	virtual bool operator<(Comparable & lhs) { return this->number > dynamic_cast<B&>(lhs).method(); };
	virtual bool operator==(Comparable & lhs) { return this->number == dynamic_cast<B&>(lhs).method(); };
	virtual bool operator>=(Comparable & lhs) { return this->number >= dynamic_cast<B&>(lhs).method(); };
	virtual bool operator<=(Comparable & lhs) { return this->number <= dynamic_cast<B&>(lhs).method(); };
	virtual bool operator!=(Comparable & lhs) { return this->number != dynamic_cast<B&>(lhs).method(); };
	virtual void print() { cout << this->number; };

private:
	int number;
};

//Sorting in non decreasing order
void printArray(Comparable ** arr) {
	for (int i = 0; i < len; i++) {
		arr[i]->print();
		cout << " ";
	}

	cout << "\n";
}
void swap(Comparable ** array, int index1, int index2) {
	Comparable * tmp = array[index1];
	array[index1] = array[index2];
	array[index2] = tmp;
}
int partition(Comparable ** array, int fromIndex, int toIndex) {
	Comparable * pivot = array[toIndex];
	int small = fromIndex - 1;

	for (int k = fromIndex; k < toIndex; k++) {
		if (*array[k] <= *pivot) {
			small++;
			swap(array, k, small);
		}
	}

	swap(array, toIndex, small + 1);
	cout << "Pivot = " << (*array[small + 1]).method() << "\n";
	printArray(array);
	return small + 1;
}


void quickSort(Comparable ** arr, int fromIndex, int toIndex) {
	if (fromIndex < toIndex) {
		int position = partition(arr, fromIndex, toIndex);
		quickSort(arr, fromIndex, position - 1);
		quickSort(arr, position + 1, toIndex);
	}
}
int main() {
	len = 7;
	Comparable ** arr = nullptr;
	arr = new Comparable*[len] { &B(9), &B(4), &B(8), &B(3), &B(1), &B(2), &B(5) };
	cout << "Initial Array : ";
	printArray(arr);
	quickSort(arr, 0, len - 1);
	return 0;
}
