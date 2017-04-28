#include <iostream>
#include <ostream>
#include <string>
#include <vector>
using namespace std;
int len;

// Test classes w/ Inheritance like model
class A {
public:
	A(int num) {};
	virtual int method() = 0;
	virtual bool operator>(A & lhs) = 0;
	virtual bool operator<(A & lhs) = 0;
	virtual bool operator==(A & lhs) = 0;
	virtual bool operator>=(A & lhs) = 0;
	virtual bool operator<=(A & lhs) = 0;
	virtual bool operator!=(A & lhs) = 0;
	virtual void print() = 0;
};

class B : virtual public A {
public:
	B(int num) : A(num) { this->number = num; }
	virtual int method() { return this->number; }
	virtual bool operator>(A & lhs) { return this->number < dynamic_cast<B&>(lhs).method(); };
	virtual bool operator<(A & lhs) { return this->number > dynamic_cast<B&>(lhs).method(); };
	virtual bool operator==(A & lhs) { return this->number == dynamic_cast<B&>(lhs).method(); };
	virtual bool operator>=(A & lhs) { return this->number >= dynamic_cast<B&>(lhs).method(); };
	virtual bool operator<=(A & lhs) { return this->number <= dynamic_cast<B&>(lhs).method(); };
	virtual bool operator!=(A & lhs) { return this->number != dynamic_cast<B&>(lhs).method(); };
	virtual void print() { cout << this->number; };

private:
	int number;
};

//Sorting in non decreasing order
void printArray(A ** arr) {
	for (int i = 0; i < len; i++) {
		arr[i]->print();
		cout << " ";
	}

	cout << "\n";
}
void swap(A ** arr, int k, int small) {
	A * temp;
	temp = arr[k];
	arr[k] = arr[small];
	arr[small] = temp;
}
int partition(A ** arr, int i, int j) {
	A * pivot = arr[j];
	int small = i - 1;

	for (int k = i; k < j; k++) {
		if (*arr[k] <= *pivot) {
			small++;
			swap(arr, k, small);
		}
	}

	swap(arr, j, small + 1);
	cout << "Pivot = " << (*arr[small + 1]).method() << "\n";
	printArray(arr);
	return small + 1;
}


void quickSort(A ** arr, int i, int j) {
	if (i < j) {
		int pos = partition(arr, i, j);
		quickSort(arr, i, pos - 1);
		quickSort(arr, pos + 1, j);
	}
}
int main() {
	len = 7;
	A ** arr = nullptr;
	arr = new A*[len] { &B(9), &B(4), &B(8), &B(3), &B(1), &B(2), &B(5) };
	cout << "Initial Array : ";
	printArray(arr);
	quickSort(arr, 0, len - 1);
	return 0;
}
