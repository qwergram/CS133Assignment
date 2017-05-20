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