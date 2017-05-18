#pragma once
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

		void push(datatype & element);
		datatype pop();

		// Overload
		virtual void push_front(datatype datum) { throw MethodNotSupported(); }
		virtual void push_back(datatype datum) { throw MethodNotSupported(); }

		virtual datatype pop_front() { throw MethodNotSupported(); }
		virtual datatype pop_back() { throw MethodNotSupported(); }
	};

	template<class datatype>
	inline void PublicQueue<datatype>::push(datatype & element)
	{
		CDLL<datatype>::push_back(element);
	}

	template<class datatype>
	inline datatype PublicQueue<datatype>::pop()
	{
		return CDLL<datatype>::pop_front();
	}
}