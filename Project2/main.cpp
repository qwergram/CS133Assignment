#include "list.h"
#include "list.cpp"
#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
using namespace std;

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
		for (unsigned int i = 0; i < mylist.getSize(); i++)
			cout << mylist[i] << " ";
		cout << endl;
		cout << "mylist[1] = 'N';" << endl;
		mylist[1] = 'N';
		cout << "mylist: " << mylist << endl;
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