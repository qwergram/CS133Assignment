#include "list.h"
#include "list.cpp"
#include "queue.h"
#include "queue.cpp"
#include "public_queue.h"
#include <iostream>
#include <cassert>
#include <exception>
#include <cstdlib>
using namespace std;
using namespace NP_ADT;

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

		// Queue Pointer Tests
		
		PublicQueue<char> * myqueue = &PublicQueue<char>(3, 'X');
		CDLL<char> * myqueue2 = &PublicQueue<char>();
		CDLL<char> * myqueue3 = &PublicQueue<char>(*myqueue);
		// CDLL<char> * myqueue4 = &PublicQueue<char>(myqueue->begin(), myqueue->end());
		cout << "myqueue: " << *myqueue << endl;
		cout << "myqueue2: " << *myqueue2 << endl;
		cout << "myqueue3: " << *myqueue3 << endl;
		// cout << "myqueue4: " << *myqueue4 << endl;
		char Y = 'Y', Z = 'Z';
		myqueue->push(Y);
		myqueue->push(Z);
		cout << myqueue->pop() << endl;
		*myqueue2 = *myqueue; // a copy
		cout << "myqueue: " << myqueue << endl;
		// create a new iterator pointing to the beginning of mylist
		PublicQueue<char>::iterator queueit(mylist.begin());
		cout << queueit++->data << " ";
		cout << queueit->data << endl;
		cout << "myqueue: ";
		for (unsigned int i = 0; i < myqueue->getSize(); i++)
			cout << (*myqueue)[i] << " ";
		cout << endl;
		cout << "myqueue[1] = 'N';" << endl;
		(*myqueue)[1] = 'N';
		cout << "myqueue: " << myqueue << endl;
		mylist.release();
		cout << "myqueue: " << myqueue << endl;
		cout << "myqueue2: " << myqueue2 << endl;
		
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