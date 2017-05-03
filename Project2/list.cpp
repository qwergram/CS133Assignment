//-----------------------------------------------------------------------------
//   File: list.cpp
//
//   Class: list
//   Functions: main
//-----------------------------------------------------------------------------


#include "list.h"

namespace NP_ADT
{
	//-------------------------------------------------------------------------
	// constructor
	//-------------------------------------------------------------------------
	template<typename datatype>
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
	NP_ADT::CDLL<datatype>::CDLL(const CDLL & cdll)
		: m_size(0), handle(nullptr)
	{
		CDLL::iterator r_it = cdll.begin();
		while (r_it != nullptr)
			push_front(*r_it++);
	}

	//-------------------------------------------------------------------------
	// constructor using iterators, copies from begin to one before end
	//-------------------------------------------------------------------------
	template<typename datatype>
	NP_ADT::CDLL<datatype>::CDLL(iterator begin, iterator end)
		:m_size(0), handle(nullptr)
	{
		while (begin != end)
			push_front(*begin++);
	}

	//-----------------------------------------------------------------------------
	// empties the list
	//-----------------------------------------------------------------------------
	template<typename datatype>
	inline void NP_ADT::CDLL<datatype>::release()
	{
		while (head() != nullptr)
			pop_front();
	}

	//-------------------------------------------------------------------------
	// prints out a list
	//-------------------------------------------------------------------------
	template<typename datatype>
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
	}

	//-------------------------------------------------------------------------
	// insert element at front of list
	//-------------------------------------------------------------------------
	template<typename datatype>
	void NP_ADT::CDLL<datatype>::push_front(datatype datum)
	{
		node* temp = new node(datum, nullptr, head());
		m_size++;
		if (!empty())
		{ // was a nonempty list
			handle->prev = temp;
			handle = temp;
		}
		else
			handle = temp;
	}

	//-------------------------------------------------------------------------
	// returns a copy of rlist
	//-------------------------------------------------------------------------
	template<typename datatype>
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
	}

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
	// removes front element and returns the data from that element
	//-------------------------------------------------------------------------
	template<typename datatype>
	datatype NP_ADT::CDLL<datatype>::pop_front()
	{
		if (handle == nullptr)
			throw runtime_error("Empty list");
		m_size--;

		datatype poppedData = head()->data;
		node * newHead = head()->next;
		if (newHead != nullptr)
			newHead->prev = handle->prev;
		
		handle = newHead;
		return poppedData;
	}

	//-------------------------------------------------------------------------
	// [] operator -- l-value
	//-------------------------------------------------------------------------
	template<typename datatype>
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
	}

	//-------------------------------------------------------------------------
	// ostream << overload
	//-------------------------------------------------------------------------
	//template<typename datatype>
	
	template <typename datatype>
	ostream & operator << (ostream& sout, const CDLL<datatype> & cdll)
	{
		
		return sout;
	}

} // end namespace NP_ADT

  //---------------------------------------------------------------------------
  // driver to test list
  //---------------------------------------------------------------------------
int main(void)
{
	using NP_ADT::CDLL; // not the same as std::list<class T>
	try
	{
		CDLL<char> mylist(3, 'X');
		CDLL<char> mylist2;
		CDLL<char> mylist3(mylist);
		CDLL<char> mylist4(mylist.begin(), mylist.end());
		cout << "mylist: " << mylist << endl;
		cout << "mylist2: " << mylist2 << endl;
		cout << "mylist3: " << mylist3 << endl;
		cout << "mylist4: " << mylist4 << endl;
		mylist.push_front('Y');
		mylist.push_front('Z');
		cout << mylist.pop_front() << endl;
		mylist2 = mylist; // a copy
		cout << "mylist: " << mylist << endl;
		// create a new iterator pointing to the beginning of mylist
		CDLL<char>::iterator listit(mylist.begin());
		cout << listit++->data << " ";
		cout << listit->data << endl;
		cout << "mylist: ";
		for (int i = 0; i < static_cast<int>(mylist.getSize()); i++)
			cout << mylist[i] << " ";
		cout << "mylist: " << endl;
		mylist.release();
		cout << "mylist: " << mylist << endl;
		cout << "mylist2: " << mylist2 << endl;
	}
	catch (exception e)
	{
		cerr << "program terminated: " << e.what() << endl;
		cin.get();
		return EXIT_FAILURE;
	}
	cin.get();  // keep window open
	return EXIT_SUCCESS;
}