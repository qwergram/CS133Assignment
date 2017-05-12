//-----------------------------------------------------------------------------
//   File: list.cpp
//
//   Class: list
//   Functions: main
//-----------------------------------------------------------------------------

#include "list.h"


using namespace std;

namespace NP_ADT
{
	// Constructors

	//-------------------------------------------------------------------------
	// constructor
	//-------------------------------------------------------------------------
	template<class datatype>
	inline CDLL<datatype>::CDLL(void) : handle(nullptr), m_size(0) {}
	
	//-------------------------------------------------------------------------
	// constructor
	//-------------------------------------------------------------------------
	template<class datatype>
	CDLL<datatype>::CDLL(size_t n_elements, datatype datum)
		:m_size(0), handle(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; i++)
			push_front(datum);
	}

	//-------------------------------------------------------------------------
	// copy constructor
	//-------------------------------------------------------------------------
	template<typename datatype>
	NP_ADT::CDLL<datatype>::CDLL(const CDLL<datatype> & cdll)
		: m_size(0), handle(nullptr)
	{
		if (!cdll.empty()) {
			CDLL::iterator r_it = cdll.begin();
			
			push_front(*r_it++);
			while (r_it != cdll.begin())
				push_front(*r_it++);
		}
	}

	//-------------------------------------------------------------------------
	// insert element at front of list
	//-------------------------------------------------------------------------
	template<typename datatype>
	void CDLL<datatype>::push_front(datatype datum)
	{
		node * temp = new node(datum, nullptr, nullptr);
		if (m_size++ == 0)
		{
			temp->next = temp;
			temp->prev = temp;
		}
		else {
			node * before = handle->prev;
			temp->next = handle;
			handle->prev = temp;
			temp->prev = before;
			before->next = temp;
		}
		handle = temp;
	}

	//-------------------------------------------------------------------------
	// insert element at end of list
	//-------------------------------------------------------------------------
	template<typename datatype>
	void CDLL<datatype>::push_back(datatype datum)
	{
		node * temp = new node(datum, nullptr, nullptr);
		if (m_size++ == 0)
		{
			temp->next = temp;
			temp->prev = temp;
			handle = temp;
		}
		else {
			node * before = handle->prev;
			temp->next = handle;
			handle->prev = temp;
			temp->prev = before;
			before->next = temp;
		}
	}

	//-------------------------------------------------------------------------
	// removes front element and returns the data from that element
	//-------------------------------------------------------------------------
	template<typename datatype>
	datatype NP_ADT::CDLL<datatype>::pop_front()
	{
		if (handle == nullptr)
			throw runtime_error("Empty list");

		datatype poppedData = head()->data;

		if (m_size-- == 1) {
			handle = nullptr;
		}
		else {
			node * oldHead = head();
			node * newHead = head()->next;
			newHead->prev = head()->prev;
			head()->prev->next = newHead;
			handle = newHead;
			delete oldHead;
		}

		return poppedData;
	}

	//-------------------------------------------------------------------------
	// removes back element and returns the data from that element
	//-------------------------------------------------------------------------
	template<typename datatype>
	datatype NP_ADT::CDLL<datatype>::pop_back()
	{
		if (handle == nullptr)
			throw runtime_error("Empty list");

		datatype poppedData = tail()->data;

		if (m_size-- == 1) {
			handle = nullptr;
		}
		else {
			node * oldTail = tail();
			node * newTail = tail()->prev;
			newTail->next = tail()->next;
			tail()->next->prev = newTail;
			delete oldTail;
		}

		return poppedData;
	}

	//-------------------------------------------------------------------------
	// returns data of the first item
	//-------------------------------------------------------------------------
	template<class datatype>
	datatype & CDLL<datatype>::front() const
	{
		if (head() != nullptr) 
			return head()->data; 
		else 
			throw runtime_error("Empty list");
	}

	//-------------------------------------------------------------------------
	// returns data of the last item
	//-------------------------------------------------------------------------
	template<class datatype>
	inline datatype & CDLL<datatype>::back() const 
	{ 
		if (tail() != nullptr) 
			return tail()->data; 
		else 
			throw runtime_error("Empty list"); 
	}

	//-----------------------------------------------------------------------------
	// empties the list
	//-----------------------------------------------------------------------------
	template<typename datatype>
	inline void NP_ADT::CDLL<datatype>::release()
	{
		while (handle != nullptr)
			pop_front();
	}

	//-------------------------------------------------------------------------
	// constructor using iterators, copies from begin to one before end
	//-------------------------------------------------------------------------
	template<typename datatype>
	NP_ADT::CDLL<datatype>::CDLL(iterator begin, iterator end)
		:m_size(0), handle(nullptr)
	{
		while (begin != end)
			push_back(*begin++);
		push_back(*begin++);
	}

	

	//-------------------------------------------------------------------------
	// prints out a list
	//-------------------------------------------------------------------------
	/*template<typename datatype>
	const datatype & NP_ADT::CDLL<datatype>::operator[](int index) const
	{
		CDLL::iterator p = x.begin(); // gets x.h
		sout << "(";
		while (p != nullptr)
		{
			sout << *p;
			if (p != x.end())
				sout << ",";
			++p; // advances iterator using next
		}
		sout << ")\n";
		return sout;
	}*/

	//-------------------------------------------------------------------------
	// returns a copy of rlist
	//-------------------------------------------------------------------------
	/*template<typename datatype>
	CDLL<datatype> NP_ADT::CDLL<datatype>::operator=(const CDLL & rlist)
	{
		if (&rlist != this)
		{
			CDLL<datatype>::iterator r_it = rlist.begin();
			release();
			while (r_it != 0)
				push_front(*r_it++);
		}
		return *this;
	}*/

	//-------------------------------------------------------------------------
	// pre-increment
	//-------------------------------------------------------------------------
	template<typename datatype>
	inline typename CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//-------------------------------------------------------------------------
	// post-increment
	//-------------------------------------------------------------------------
	template<typename datatype>
	inline typename CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	//-------------------------------------------------------------------------
	// pre-decrement
	//-------------------------------------------------------------------------
	template<typename datatype>
	inline typename CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator--()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->prev;
		return *this;
	}

	//-------------------------------------------------------------------------
	// post-decrement
	//-------------------------------------------------------------------------
	template<typename datatype>
	inline typename CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}



	//-------------------------------------------------------------------------
	// [] operator -- l-value
	//-------------------------------------------------------------------------
	/*template<typename datatype>
	datatype & NP_ADT::CDLL<datatype>::operator[](int index)
	{
		iterator it;
		if (index >= 0)
		{
			if (index >= static_cast<int>(getSize()))
				throw out_of_range("index out-of-range");
			it = begin();
			for (int i = 0; i < index; i++)
				it++;
		}
		else
		{
			if (index < -(static_cast<int>(getSize())))
				throw out_of_range("index out-of-range");
			it = end();
			for (int i = -1; i > index; i--)
				it--;
		}
		return *it;
	}*/

	//-------------------------------------------------------------------------
	// ostream << overload
	//-------------------------------------------------------------------------
	template <typename datatype>
	ostream & operator << (ostream& sout, const CDLL<datatype> & cdll)
	{
		auto it = cdll.begin();
		sout << "[";
		if (!cdll.empty()) {
			while (it != cdll.end())
				sout << *it++ << ", ";
			sout << *it;
		}
		sout << "]";
		return sout;
	}

} // end namespace NP_ADT

