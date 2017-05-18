#pragma once
#pragma once
#include "list.h"

namespace NP_ADT {

	template <class datatype>
	class Queue : virtual public CDLL<datatype> {
	public:

		Queue(void)
			: CDLL<datatype>::CDLL() {}
		Queue(size_t n_elements, datatype datum)
			: CDLL<datatype>::CDLL(n_elements, datum) { };
		Queue(const CDLL & queue)
			: CDLL<datatype>::CDLL(queue) { };
		Queue(iterator begin, iterator end)
			: CDLL<datatype>::CDLL(begin, end) { };

		virtual ~ProtectedQueue() { release(); };

		unsigned getSize() const;
		bool empty() const { return (handle == nullptr); };

		void release() { while (handle != nullptr) { pop(); } }

		iterator begin() const { return CDLL<datatype>::begin(); }
		iterator end() const { return CDLL<datatype>::end(); }

		void push(datatype & element);
		datatype pop();

		node * head() { return handle; }
		node * tail() { return (handle == nullptr) ? nullptr : handle->prev; }
	protected:
		// node * handle;
		// unsigned m_size; // number of elements in the list 
	};
}