//-----------------------------------------------------------------------------
// File: list.cpp
// Description: Contains all the non-inline methods for list.h
// this file must be included for full cdll functionality.
//-----------------------------------------------------------------------------

#include "list.h"


using namespace std;

namespace NP_ADT
{
	//-------------------------------------------------------------------------
	// Function: Constructor		
	// Description:	Element Repetition
	// Called By: main
	// Calls: push_front
	// Parameters: n_elements, datum
	// Throws: out_of_range if n_elements is invalid
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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
	// Function: Constructor		
	// Description:	Copy Constructor
	// Called By: main
	// Calls: release, push_back, begin, empty, end
	// Parameters: &rlist
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype>
	NP_ADT::CDLL<datatype>::CDLL(const CDLL<datatype> & rlist)
		: m_size(0), handle(nullptr)
	{
		if (&rlist != this && !rlist.empty())
		{
			auto r_it = rlist.begin();
			release();
			while (r_it != rlist.end())
				push_back(*r_it++);
			push_back(*r_it);
		}
	}

	//-------------------------------------------------------------------------
	// Function: push_front
	// Description:	Insert in front of list
	// Called By: ctors, main
	// Calls: node ctor
	// Parameters: datum
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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
	// Function: push_back	
	// Description:	add item to the end of a list
	// Called By: ctors, main
	// Calls: node()
	// Parameters: datum
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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
	// Function: pop_front		
	// Description:	remove the first item of the list and return the value
	// Called By: release, main
	// Calls: head
	// Returns: datatype  
	// Throws: runtime_error if empty list
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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
	// Function: pop_back	
	// Description:	return the last item of the cdll and return the value
	// Called By: main
	// Calls: tail
	// Returns: datatype  
	// Throws: runtime_error if list is empty
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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
	// Function: front()
	// Description:	return the first item in the cdll
	// Called By: pop_front
	// Returns: &datatype
	// Throws: runtime_error if empty list
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<class datatype>
	datatype & CDLL<datatype>::front() const
	{
		if (head() != nullptr) 
			return head()->data; 
		else 
			throw runtime_error("Empty list");
	}


	//-------------------------------------------------------------------------
	// Function: back()
	// Description:	Returns the data of the last item 
	// Called By: pop_back
	// Returns: &datatype
	// Throws: runtime_error if empty list
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<class datatype>
	inline datatype & CDLL<datatype>::back() const 
	{ 
		if (tail() != nullptr) 
			return tail()->data; 
		else 
			throw runtime_error("Empty list"); 
	}

	//-------------------------------------------------------------------------
	// Function: release()
	// Description:	empties the list
	// Called By: destructor
	// Calls: pop_front
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype>
	inline void NP_ADT::CDLL<datatype>::release()
	{
		while (handle != nullptr)
			pop_front();
	}

	//-------------------------------------------------------------------------
	// Function: Constructor
	// Description:	Constructor takes inclusive iterator bounds
	// Called By: main
	// Calls: push_back
	// Parameters: begin, end
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype>
	NP_ADT::CDLL<datatype>::CDLL(iterator begin, iterator end)
		:m_size(0), handle(nullptr)
	{
		while (begin != end)
			push_back(*begin++);
		push_back(*begin++);
	}

	//-------------------------------------------------------------------------
	// Function: operator[] const
	// Description:	return the value at the index 
	// Called By: main
	// Calls: begin
	// Parameters: index
	// Returns: &datatype
	// Throws: out_of_range of index is invalid
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype>
	const datatype & NP_ADT::CDLL<datatype>::operator[](int index) const
	{
		if (index >= int(m_size) || index < 0) 
			throw out_of_range("out of range");
		
		const iterator cursor = begin();
		for (int x = 0; x < index; x++) { cursor++; }
		return *cursor;
	}

	//-------------------------------------------------------------------------
	// Function: operator[]
	// Description:	returns a mutable nth item of the list
	// Called By: main
	// Calls: begin
	// Parameters: index
	// Returns: &datatype
	// Throws: out_of_range of index is invalid
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<class datatype>
	datatype & NP_ADT::CDLL<datatype>::operator[](int index)
	{
		if (index >= int(m_size) || index < 0)
			throw out_of_range("out of range");

		iterator cursor = begin();
		for (int x = 0; x < index; x++) { cursor++; }
		return *cursor;
	}

	//-------------------------------------------------------------------------
	// Function: operator=
	// Description:	creates a deep copy of a list
	// Called By: main
	// Calls: empty, begin, release, end, push_back
	// Parameters: &rlist
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype>
	CDLL<datatype> NP_ADT::CDLL<datatype>::operator=(const CDLL & rlist)
	{
		if (&rlist != this && !rlist.empty())
		{
			auto r_it = rlist.begin();
			release();
			while (r_it != rlist.end())
				push_back(*r_it++);
			push_back(*r_it);
		}
		return *this;
	}

	//-------------------------------------------------------------------------
	// Function: iterator operator++
	// Description:	pre incrementor for iterator
	// Called By: main
	// Returns: iterator
	// Throws: runtime_error if nullptr
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype> inline typename 
	CDLL<datatype>::iterator CDLL<datatype>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//-------------------------------------------------------------------------
	// Function: iterator operator++
	// Description:	post incrementor for iterator
	// Called By: main
	// Returns: iterator
	// Throws: runtime_error if nullptr 
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype> inline typename
	CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	//-------------------------------------------------------------------------
	// Function: iterator operator--
	// Description:	pre decrement for iterator
	// Called By: main
	// Returns: iterator
	// Throws: runtime_error if nullptr
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype> inline typename
	CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator--()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->prev;
		return *this;
	}

	//-------------------------------------------------------------------------
	// Function: iterator operator--
	// Description:	post decrement for iterator
	// Called By: main
	// Returns: iterator
	// Throws: runtime_error if nullptr 
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
	template<typename datatype> inline typename
	CDLL<datatype>::iterator NP_ADT::CDLL<datatype>::iterator::operator--(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->prev;
		return temp;
	}

	//-------------------------------------------------------------------------
	// Function: ostream operator <<
	// Description:	push string representation of a list to ostream
	// Called By: main
	// Calls: begin, empty, end
	// Parameters: sout, cdll
	// Returns: sout
	// History Log:
	// https://github.com/qwergram/CS133Assignment/blame/master/Project2/list.cpp
	// ------------------------------------------------------------------------
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

