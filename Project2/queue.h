#pragma once
#include "list.h"

namespace NP_ADT {

	template <class datatype>
	class Queue : virtual protected CDLL<datatype> {
	public:

		Queue(void) 
			: // handle(nullptr), m_size(0),
			CDLL<datatype>::CDLL() {}
		Queue(size_t n_elements, datatype datum) 
			: // handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(n_elements, datum) { };
		Queue(const CDLL & queue) 
			: // handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(queue) { };
		Queue(iterator begin, iterator end) 
			: // handle(nullptr), m_size(0), 
			CDLL<datatype>::CDLL(begin, end) { };
		
		virtual ~Queue() { release(); };

		virtual unsigned getSize() const;
		virtual bool empty() const { return (handle == nullptr); };
		
		void release() { while (handle != nullptr) { pop(); } }

		iterator begin() const { return head(); }
		iterator end() const { return tail(); }
		
		void push(datatype & element);
		datatype & pop();

		node * head() { return handle; }
		node * tail() { return (handle == nullptr) ? nullptr : handle->prev; }
	protected:
		// node * handle;
		// unsigned m_size; // number of elements in the list 
	};
}