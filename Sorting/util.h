#pragma once
#include <iostream>
#include <string>
#include <vector>
namespace std {
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
		virtual bool operator>(A & lhs) { return this->number > dynamic_cast<B&>(lhs).method(); };
		virtual bool operator<(A & lhs) { return this->number < dynamic_cast<B&>(lhs).method(); };
		virtual bool operator==(A & lhs) { return this->number == dynamic_cast<B&>(lhs).method(); };
		virtual bool operator>=(A & lhs) { return this->number >= dynamic_cast<B&>(lhs).method(); };
		virtual bool operator<=(A & lhs) { return this->number <= dynamic_cast<B&>(lhs).method(); };
		virtual bool operator!=(A & lhs) { return this->number != dynamic_cast<B&>(lhs).method(); };
		virtual void print() { cout << this->number << ' '; };

	private:
		int number;
	};
}