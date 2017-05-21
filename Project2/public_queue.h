//-----------------------------------------------------------------------------
//   Title: circular queue
//   Description: This file contains the class 
//				  definition for queue
//
//   Programmer: 
//    Norton Pengra
// 
//   Date: original: Spring 2017
//   Version: 1.10
//
//   Environment: Intel Xeon PC
//     Software: MS Windows 10 for execution;
//     Compiles under Microsoft Visual C++.Net 2017
//
//   class publicqueue : (inherits from cdll)
//
//     Methods:
// 
//       inline: 
//         queue() -- construct the empty list
//         queue(size_t n_elements, datatype datum) -- create a 
//					list of a specific size, all elements the same
//         ~queue() -- destructor
//         unsigned getSize()const  -- accessor, returns m_size
//         iterator begin()const -- returns address of first element
//         iterator end()const -- returns address of last element
//         bool empty()const -- true if no elements
//         void push(datatype datum) -- insert element at back of queue 
//         datatype pop(); -- removes front element and returns the data 
//									from that element
//		   All other methods are overridden and will throw an exception
//		   if called.
//
//
//   History Log:
//	   May 18, 2017, NP completed version 1.10
//-----------------------------------------------------------------------------

#pragma once
#include "list.h"
#include "npadtexcept.h"

namespace NP_ADT {

	template <class datatype>
	class PublicQueue : public CDLL<datatype> {
	public:
		PublicQueue(void)
			: CDLL<datatype>::CDLL() {}
		PublicQueue(size_t n_elements, datatype datum)
			: CDLL<datatype>::CDLL(n_elements, datum) { };
		PublicQueue(const CDLL & queue)
			: CDLL<datatype>::CDLL(queue) { };
		PublicQueue(iterator begin, iterator end)
			: CDLL<datatype>::CDLL(begin, end) { };

		virtual ~PublicQueue() { release(); };

		void push(datatype & element) { CDLL<datatype>::push_back(element); }
		datatype pop() { return CDLL<datatype>::pop_front(); }

		// Overload
		virtual void push_front(datatype datum) { throw MethodNotSupported(); }
		virtual void push_back(datatype datum) { throw MethodNotSupported(); }

		virtual datatype pop_front() { throw MethodNotSupported(); }
		virtual datatype pop_back() { throw MethodNotSupported(); }

		datatype & operator[](int index) { throw MethodNotSupported(); };
		const datatype & operator[](int index) const { throw MethodNotSupported(); };
	};

}