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
	datatype & Queue<datatype>::pop()
	{
		datatype popped_value = CDLL<datatype>::pop_front();
		datatype & popped_value_reference = popped_value;
		return popped_value_reference;
	}

}