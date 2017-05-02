//-----------------------------------------------------------------------------
//   File: list.cpp
//
//   Class: list
//   Functions: main
//-----------------------------------------------------------------------------


#include "list.h"

namespace NP_ADT
{
	//-----------------------------------------------------------------------------
	// constructor
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL<datatype>::DLCL(size_t n_elements, datatype datum)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		if (n_elements <= 0)
			throw out_of_range("Empty list");
		for (size_t i = 0; i < n_elements; ++i)
			push_front(datum);
	}

	//-----------------------------------------------------------------------------
	// copy constructor
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL<datatype>::DLCL(const DLCL & x)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		DLCL::iterator r_it = x.begin();
		while (r_it != nullptr)
			push_front(*r_it++);
	}

	//-----------------------------------------------------------------------------
	// constructor using iterators, copies from b to one before e
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL<datatype>::DLCL(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (b != e)
			push_front(*b++);
	}

	//-----------------------------------------------------------------------------
	// empties the list
	//-----------------------------------------------------------------------------
	template<class datatype> void DLCL<datatype>::release()
	{
		while (head != nullptr)
			pop_front();
	}

	//-----------------------------------------------------------------------------
	// prints out a list
	//-----------------------------------------------------------------------------
	template<class datatype> ostream & operator << (ostream& sout, const DLCL<datatype> & x)
	{
		DLCL::iterator p = x.begin(); // gets x.h
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

	//-----------------------------------------------------------------------------
	// insert element at front of list
	//-----------------------------------------------------------------------------
	template<class datatype> void DLCL<datatype>::push_front(datatype datum)
	{
		listelem* temp = new listelem(datum, nullptr, head);
		m_size++;
		if (!empty())
		{ // was a nonempty list
			head->prev = temp;
			head = temp;
		}
		else
			head = tail = temp;
	}

	//-----------------------------------------------------------------------------

	// returns a copy of rlist
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL DLCL<datatype>::operator=(const DLCL & rlist)
	{
		if (&rlist != this)
		{
			DLCL::iterator r_it = rlist.begin();
			release();
			while (r_it != 0)
				push_front(*r_it++);
		}
		return *this;
	}

	//-----------------------------------------------------------------------------
	// pre-increment
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL::iterator DLCL<datatype>::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// post-increment
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL::iterator DLCL<datatype>::iterator::operator++(int)
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		iterator temp = *this;
		ptr = ptr->next;
		return temp;
	}

	

	//-----------------------------------------------------------------------------
	// pre-decrement
	//-----------------------------------------------------------------------------
	template<class datatype> DLCL::iterator DLCL<datatype>::iterator::operator--()
	{
		// REPLACE THE DUMMY CODE BELOW WITH YOUR OWN
		iterator temp = nullptr;
		return temp;

	}

	//-----------------------------------------------------------------------------
	// post-decrement
	//-----------------------------------------------------------------------------
	template<class datatype> iterator DLCL<datatype>::iterator::operator--(int)
	{
		// REPLACE THE DUMMY CODE BELOW WITH YOUR OWN
		iterator temp = nullptr;
		return temp;
	}

	//-----------------------------------------------------------------------------
	// removes front element and returns the data from that element
	//-----------------------------------------------------------------------------
	template<class datatype> datatype DLCL<datatype>::pop_front()
	{
		if (head == nullptr)
			throw runtime_error("Empty list");
		m_size--;
		datatype data = head->data;
		iterator temp = begin();
		temp++;
		delete head;
		head = temp;
		if (!empty())
			head->prev = nullptr;
		else
			tail = nullptr; // empty at both ends
		return data;
	}

	//-----------------------------------------------------------------------------
	// [] operator -- l-value
	//-----------------------------------------------------------------------------
	template<class datatype> datatype & DLCL<datatype>::operator[](int index)
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
	//-----------------------------------------------------------------------------
	// [] operator -- r-value
	//-----------------------------------------------------------------------------
	template<class datatype> const datatype & DLCL<datatype>::operator[](int index)const
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

} // end namespace PB_ADT

  //-----------------------------------------------------------------------------
  // driver to test list
  //-----------------------------------------------------------------------------
int main(void)
{
	using NP_ADT::DLCL; // not the same as std::list<class T>
	try
	{
		DLCL<char> mylist(3, 'X');
		DLCL<char> mylist2;
		DLCL<char> mylist3(mylist);
		DLCL<char> mylist4(mylist.begin(), mylist.end());
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
		DLCL<char>::iterator listit(mylist.begin());
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