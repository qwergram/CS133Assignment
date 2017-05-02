#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
using namespace std;

namespace PB_ADT {

	typedef char datatype;

	class list
	{
	public:
		struct listelem; // forward declarations
		class iterator;
		// constructors
		list() : head(nullptr), tail(nullptr), m_size(0) {}
		list(size_t n_elements, datatype datum);
		list(const list& x);
		list(iterator b, iterator e);

		~list() { release(); }
		unsigned getSize() const { return m_size; }
		iterator begin() const { return head; }
		iterator end() const { return tail; }
		void push_front(datatype datum);
		datatype pop_front();
		void push_back(datatype datum);
		datatype pop_back();
		datatype& front() const { return head->data; }
		datatype& back() const { return tail->data; }
		bool empty()const { return head == nullptr || tail == nullptr; }
		void release();
		list operator=(const list & rlist);
		datatype& operator[](int index);
		const datatype& operator[](int index) const;
	private:
		listelem *head;
		listelem *tail;
		unsigned m_size; // number of elements in the list 
	public:
		struct listelem // list cell
		{
			datatype data;
			listelem *next;
			listelem *prev;
			listelem(datatype datum, listelem* p, listelem* n) : data(datum), prev(p), next(n) {} // struct constructor
		};
		// scoped within class list !
		class iterator
		{
		public:
			iterator(listelem* p = nullptr) : ptr(p) {}
			iterator operator++();
			iterator operator--();
			iterator operator++(int);
			iterator operator--(int);
			listelem* operator->() const { return ptr; }
			datatype& operator*() const { return ptr->data; }
			operator listelem*() const { return ptr; }
		private:
			listelem* ptr; //current listelem or nullptr
		};
	};

	ostream& operator<<(ostream& sout, const list& x);

}