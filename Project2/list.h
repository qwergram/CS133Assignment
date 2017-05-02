#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
using namespace std;

//-----------------------------------------------------------------------------
//   Title: list Class
//   Description: This file contains the class definition for list, with a test driver
//
//   Programmer: 
//    Object Oriented Programming Using C++, Edition 2 By Ira Pohl
//      modified by Paul Bladek
// 
//   Date: original: Summer 1996
//   Version: 1.06
//
//   Environment: Intel Xeon PC
//     Software: MS Windows 7 for execution;
//     Compiles under Microsoft Visual C++.Net 2010
//
//   class list:
//
//     Properties:
//       listelem *head -- front end of list
//       listelem *tail -- back end of list
//       unsigned m_size -- number of elements in the list
//
//     Methods:
// 
//       inline: 
//         list() -- construct the empty list
//         list(size_t n_elements, datatype datum) -- create a list of a specific size, all elements the same
//         ~list() { release(); } -- destructor
//         unsigned getSize()const  -- accessor, returns m_size
//         iterator begin()const -- returns address of first element
//         iterator end()const -- returns address of last element
//         datatype& front()const  -- returns first element data
//         datatype& back()const -- returns last element data
//         bool empty()const -- true if no elements
//
//       non-inline:
//         list(const list& x); -- copy constructor
//         list(iterator b, iterator e) -- constructor using iterators
//         void push_front(datatype datum) -- insert element at front of list
//         datatype pop_front(); -- removes front element and returns the data from that element
//         void push_back(datatype datum) -- insert element at back of list 
//         datatype pop_back() -- removes back element and returns the data from that element
//         void release() -- removes all items from list
//         list operator=(const list & rlist) -- returns a copy of rlist
//         datatype& operator[](int index) -- for l-value
//         const datatype& operator[](int index)const -- for r-value
//
//    Public Nested Structures:
//
//      struct listelem -- list cell
//
//        properties:
//          datatype data -- the actual datum
//          listelem *next -- forward link
//          listelem *prev -- backward link
//        constructor:
//          listelem(datatype c, listelem* p, listelem* n, listelem* p) -- struct constructor
//
//     class iterator
//        Public Methods
// 
//           inline: 
//            listelem* operator->() -- same as for pointer
//            datatype& operator*() -- same as for pointer
//            operator listelem*() -- conversion
//            iterator(listelem* p = nullptr) -- constructor
// 
//           non-inline: 
//            iterator operator++() -- pre-increment
//            iterator operator--() -- pre-decrement
//            iterator operator++(int) -- post-increment
//            iterator operator--(int) -- post-decrement
// 
//        Private Properties
//            listelem* ptr -- current listelem or NULL
//
//   History Log:
//     summer, 1996 original  IP completed version 1.0 
//     May 11, 2000,  PB  completed version 1.01 
//     March 8, 2002, PB  completed version 1.02 
//     April 10, 2003, PB  completed version 1.03 
//     April 30, 2003, PB  completed version 1.04 
//     May 10, 2005, PB  completed version 1.05 
//     April 15, 2008, PB  completed version 1.06
//     April 20, 2010, PB completed version 1.07 
//     April 15, 2011, PB completed version 1.09 
//-----------------------------------------------------------------------------


namespace NP_ADT {

	typedef char datatype;

	class DLCL
	{
	public:
		struct listelem; // forward declarations
		class iterator;
		// constructors
		DLCL() : head(nullptr), tail(nullptr), m_size(0) {}
		DLCL(size_t n_elements, datatype datum);
		DLCL(const DLCL& x);
		DLCL(iterator b, iterator e);

		~DLCL() { release(); }
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
		DLCL operator=(const DLCL & rlist);
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

	ostream& operator<<(ostream& sout, const DLCL& x);

}