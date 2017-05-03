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
	list::list(size_t n_elements, datatype datum)
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
	list::list(const list& x)
		: m_size(0), head(nullptr), tail(nullptr)
	{
		list::iterator r_it = x.begin();
		while (r_it != nullptr)
			push_front(*r_it++);
	}

	//-----------------------------------------------------------------------------
	// constructor using iterators, copies from b to one before e
	//-----------------------------------------------------------------------------
	list::list(iterator b, iterator e)
		:m_size(0), head(nullptr), tail(nullptr)
	{
		while (b != e)
			push_front(*b++);
	}

	//-----------------------------------------------------------------------------
	// empties the list
	//-----------------------------------------------------------------------------
	void list::release()
	{
		while (head != nullptr)
			pop_front();
	}

	//-----------------------------------------------------------------------------
	// prints out a list
	//-----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const list& x)
	{
		list::iterator p = x.begin(); // gets x.h
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
	void list::push_front(datatype datum)
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
	list list::operator=(const list & rlist)
	{
		if (&rlist != this)
		{
			list::iterator r_it = rlist.begin();
			release();
			while (r_it != 0)
				push_front(*r_it++);
		}
		return *this;
	}

	//-----------------------------------------------------------------------------
	// pre-increment
	//-----------------------------------------------------------------------------
	list::iterator list::iterator::operator++()
	{
		if (ptr == nullptr)
			throw runtime_error("nullptr pointer");
		ptr = ptr->next;
		return *this;
	}

	//-----------------------------------------------------------------------------
	// post-increment
	//-----------------------------------------------------------------------------
	list::iterator list::iterator::operator++(int)
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
	list::iterator list::iterator::operator--()
	{
		// REPLACE THE DUMMY CODE BELOW WITH YOUR OWN
		iterator temp = nullptr;
		return temp;

	}

	//-----------------------------------------------------------------------------
	// post-decrement
	//-----------------------------------------------------------------------------
	list::iterator list::iterator::operator--(int)
	{
		// REPLACE THE DUMMY CODE BELOW WITH YOUR OWN
		iterator temp = nullptr;
		return temp;
	}

	//-----------------------------------------------------------------------------
	// removes front element and returns the data from that element
	//-----------------------------------------------------------------------------
	datatype list::pop_front()
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
	datatype& list::operator[](int index)
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
	const datatype& list::operator[](int index)const
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
	using NP_ADT::list; // not the same as std::list<class T>
	try
	{
		list mylist(3, 'X');
		list mylist2;
		list mylist3(mylist);
		list mylist4(mylist.begin(), mylist.end());
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
		list::iterator listit(mylist.begin());
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