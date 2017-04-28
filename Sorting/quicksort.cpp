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
void swap(Comparable ** arr, int index1, int index2) {
	Comparable * temp;
	temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}
int partition(Comparable ** arr, int fromIndex, int toIndex) {
	Comparable * pivot = arr[toIndex];
	int small = fromIndex - 1;

	for (int k = fromIndex; k < toIndex; k++) {
		if (*arr[k] <= *pivot) {
			small++;
			swap(arr, k, small);
		}
	}

	swap(arr, toIndex, small + 1);
	cout << "Pivot = " << (*arr[small + 1]).method() << "\n";
	printArray(arr);
	return small + 1;
}


void quickSort(Comparable ** arr, int fromIndex, int toIndex) {
	if (fromIndex < toIndex) {
		int pos = partition(arr, fromIndex, toIndex);
		quickSort(arr, fromIndex, pos - 1);
		quickSort(arr, pos + 1, toIndex);
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
