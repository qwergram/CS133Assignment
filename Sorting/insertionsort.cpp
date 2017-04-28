//Insertion sort
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
	virtual void print() { cout << this->number << ' '; };

private:
	int number;
};

//Sorting in non decreasing order
void printArray(A ** array, int size) {
	for (int index = 0; index < size; index++)
		array[index]->print();

	cout << "\n";
}
void insertionsort(A ** array, int size) {
	for (int outerIndex = 1; outerIndex < size; outerIndex++) {
		int innerIndex = outerIndex - 1;
		A * temp = array[outerIndex];

		while (innerIndex >= 0 && *temp < *array[innerIndex]) {
			array[innerIndex + 1] = array[innerIndex];
			innerIndex--;
		}

		array[innerIndex + 1] = temp;
		cout << "After pass " << outerIndex << "  : ";
		//Printing array after pass
		printArray(array, size);
	}
}
int main() {
	int size = 9;
	A ** array = nullptr;
	array = new A*[size] { &B(1), &B(7), &B(3), &B(0), &B(3), &B(1), &B(9), &B(9), &B(7) };
	cout << "Initial Array : ";
	printArray(array, size);
	insertionsort(array, size);
	return 0;
}