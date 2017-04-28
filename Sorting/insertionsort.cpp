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
void printArray(A ** arr, int len) {
	for (int i = 0; i < len; i++)
		arr[i]->print();

	cout << "\n";
}
void insertionsort(A ** arr, int len) {
	for (int i = 1; i < len; i++) {
		int j = i - 1;
		A * temp = arr[i];

		while (j >= 0 && *temp < *arr[j]) {
			arr[j + 1] = arr[j];
			j--;;
		}

		arr[j + 1] = temp;
		cout << "After pass " << i << "  : ";
		//Printing array after pass
		printArray(arr, len);
	}
}
int main() {
	int len = 9;
	A ** arr = nullptr;
	arr = new A*[len] { &B(1), &B(7), &B(3), &B(0), &B(3), &B(1), &B(9), &B(9), &B(7) };
	cout << "Initial Array : ";
	printArray(arr, len);
	insertionsort(arr, len);
	return 0;
}