#pragma once
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

	// typedef char datatype;

	template <class datatype>
	class CDLL
	{
	public:
		struct node;
		class iterator;
		
		// Constructors
		CDLL() : handle(nullptr), m_size(0) {}
		CDLL(size_t n_elements, datatype datum);
		CDLL(const CDLL& cdll);
		//CDLL(iterator begin, iterator end);
		
		// Destructor
		~CDLL() { release(); }

		unsigned getSize() const { return m_size; }
		iterator begin() const { return head(); }
		iterator end() const { return tail(); }
		void push_front(datatype datum);
		void push_back(datatype datum);
		datatype pop_front();
		datatype pop_back();
		datatype & front() const;
		datatype & back() const;
		bool empty() const { return handle == nullptr; }
		void release();
		// CDLL operator=(const CDLL & rlist);
		// datatype& operator[](int index);
		// const datatype& operator[](int index) const;

		// Head = handle and tail = handle - 1
		node * head(void) const { return handle; }
		node * tail(void) const { return (handle == nullptr) ? nullptr : handle->prev; }

	private:
		// remove head and tail as property
		// and only keep track of one handle
		node * handle;
		unsigned m_size; // number of elements in the list 

	public:
		struct node
		{
			datatype data;
			node * next;
			node * prev;
			node(datatype datum, node * prev_, node * next_) : data(datum), prev(prev_), next(next_) {} // struct constructor
		};

		class iterator
		{
		public:
			iterator(node * p = nullptr) : ptr(p) {}
			//iterator operator++();
			//iterator operator--();
			//iterator operator++(int);
			//iterator operator--(int);
			node * operator->() const { return ptr; }
			datatype & operator*() const { return ptr->data; }
			operator node*() const { return ptr; }
		private:
			node * ptr;
		};
	};

	//template <typename datatype>
	//ostream & operator<<(ostream& sout, const CDLL<datatype> & cdll);

}