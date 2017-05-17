#include "queue.h"

namespace NP_ADT {
	template<class datatype>
	inline unsigned Queue<datatype>::getSize() const
	{
		return CDLL<datatype>::getSize();
	}

	template<class datatype>
	void Queue<datatype>::push(datatype & element)
	{
		push_back(element);
	}

	template<class datatype>
	datatype Queue<datatype>::pop()
	{
		return CDLL<datatype>::pop_front();
	}

}