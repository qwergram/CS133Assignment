#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <new>


using namespace std;

template<class T>
class arrayclass {
public:
	typedef const T* const_iterator;
	arrayclass(int size = 0) 
		: m_capacity(size), m_size(0), m_array(nullptr) {
		if (size < 0) {
			ostringstream oss;
			oss << "cannot create an arrayclass of cpacity " << size;
			throw domain_error(oss.str().c_str());
		} 
		if (size > 0)
			m_array = new T[size];
	}
	
	arrayclass(const arrayclass<T> & original);

	bool full() const { return m_size >= m_capacity; }
	bool empty() const { return m_size == 0; }
	int get_capacity() const { return m_capacity; };
	int get_size() const { return m_size; }

	const_iterator begin() { return m_array; }
	const_iterator end() { return m_array + m_size; }
	T at(int index) const {
		if (index >= m_size || index < 0)
			throw out_of_range("index out of range");
		return m_array[index];
	}
	~arrayclass() { if (m_array != nullptr) delete[] m_array; }

protected:
	T* m_array;
	int m_size;
private:
	int m_capacity;
};

template<class T>
arrayclass<T>::arrayclass(const arrayclass<T>& original)
	: m_array(nullptr), m_size(original.get_size()), 
	m_capacity(original.get_capacity()) 
{
	m_array = new T[m_capacity];
	for (int i = 0; i < m_size; i++) {
		m_array[i] = original.at(i);
	}
}

template <class T>
class arrayStack : public arrayclass<T> {
public:
	arrayStack(int size = 0) : arrayclass(size) {}
	arrayStack(const arrayStack & other) : arrayclass(other) {}
	void push(T item) {
		if (full()) throw domain_error("array is full");
		m_array[m_size++] = item;
	}
	T pop() {
		if (m_size != 0)
			return m_array[--m_size];
		throw domain_error("array is empty");
	}
};

int main(void) {
	arrayStack<long> **st = nullptr;
	arrayStack<long> singleStack(5);
	long element = 3L;
	int numElements = 2;
	int exitCode = EXIT_SUCCESS;
	try {
		/* ** B CORRECTION ** ( -9 pts )
			I previously thought you needed some double pointer
			magic to make this work, but I was wrong. You only
			need one pointer when declaring an array or pointers.
		*/
		arrayStack<long> * st[2]{
			new arrayStack<long>(3),
			new arrayStack<long>(2)
		};
		
		/* ** C CORRECTION ** ( -6 pts )
			Ranges in the second argument of for loop arguments were
			incorrect. Changed them to cover 3, 4, 5 and 6, 7 
			respectively.
		*/
		for (long i = 3; i < 6; st[0]->push(i++));
		for (long i = 6; i < 8; st[1]->push(i++));

		/* ** D CORRECTION ** ( -6 pts )
			Previously thought `iterator` was a builtin I could use
			to reference to `st[i]->begin()`. Instead, I should've 
			used `arrayStack<long>::const_iterator`. I also had the 
			wrong index in the first for loop; it should've been 
			`i < 2` and not `i < 3`.
		*/
		for (short i = 0; i < 2; i++) {
			for (arrayStack<long>::const_iterator k = st[i]->begin();
				k != st[i]->end(); k++) {
				cout << *k << ' ';
			}
			cout << endl;
			while (!st[i]->empty()) {
				singleStack.push(st[i]->pop() + 1);
			}
			while (!singleStack.empty()) {
				st[i]->push(singleStack.pop());
			}
		}

	}
	/* ** A & E CORRECTION ( -4 pts ) **
		Forgot to catch `domain_error`s and fixed index error in other for loop
		again.
	*/
	catch (bad_alloc) {
		exitCode = EXIT_FAILURE;
	}
	catch (domain_error) {
		exitCode = EXIT_FAILURE;
	}
	if (st != nullptr) {
		for (int i = 0; i < 2; i++)
			delete st[i];
		delete[] st;
	}
	return exitCode;
}

