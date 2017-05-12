#pragma once
#include "list.h"

namespace NP_ADT {

	template <class datatype>
	class Queue : virtual protected CDLL<datatype> {
	public:
		Queue() : handle(nullptr), m_size(0) {}
		Queue(size_t n_elements, datatype datum);
		Queue(const CDLL& cdll);
		Queue(iterator begin, iterator end);

		~Queue() { };

		unsigned getSize() const;
		bool empty() const;
		void release();

		iterator begin() const { return head(); }
		iterator end() const { return tail(); }
		
		void push(datatype & element);
		datatype & pop();


	};
}