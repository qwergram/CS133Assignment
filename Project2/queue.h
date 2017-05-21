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
//   class queue : (inherits from cdll)
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
//
//
//   History Log:
//	   May 18, 2017, NP completed version 1.10
//-----------------------------------------------------------------------------

#pragma once
#include "list.h"

namespace NP_ADT {

	template <class datatype>
	class Queue : protected CDLL<datatype> {
	public:
		using CDLL::CDLL;
		
		virtual ~Queue() { release(); };

		unsigned getSize() const { return CDLL<datatype>::getSize(); }
		bool empty() const { return (handle == nullptr); };
		
		void release() { while (handle != nullptr) { pop(); } }

		iterator begin() const { return CDLL<datatype>::begin(); }
		iterator end() const { return CDLL<datatype>::end(); }
		
		void push(datatype & element) { push_back(element); }
		datatype pop() { return CDLL<datatype>::pop_front(); }

		node * head() { return handle; }
		node * tail() { return (handle == nullptr) ? nullptr : handle->prev; }
	};

}