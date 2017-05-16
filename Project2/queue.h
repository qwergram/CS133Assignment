#pragma once
#include "list.h"

namespace NP_ADT {

	template <class datatype>
	class Queue : virtual protected CDLL<datatype> {
	public:
		Queue(void) 
			: handle(nullptr), m_size(0),
			CDLL<datatype>::CDLL() {}
		Queue(size_t n_elements, datatype datum) 
			: handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(n_elements, datum) { };
		Queue(const CDLL & queue) 
			: handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(queue) { };
		Queue(iterator begin, iterator end) 
			: handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(begin, end) { };
		
		~Queue() { release(); };

		unsigned getSize() const { return m_size; }
		bool empty() const { return CDLL<datatype>::empty(); }
		
		void release() { while (handle != nullptr) { pop(); } }

		iterator begin() const { return head(); }
		iterator end() const { return tail(); }
		
		void push(datatype & element) { CDLL<datatype>::push_back(element); m_size++; }
		// void push(datatype element) { CDLL<datatype>::push_back(element); m_size++; }
		datatype & pop() { m_size--; return CDLL<datatype>::pop_front(); }

		node * head() { return CDLL<datatype>::head(); }
		node * tail() { return CDLL<datatype>::tail(); }
	protected:
		node * handle;
		unsigned m_size; // number of elements in the list 
	};
}