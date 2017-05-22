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

//-------------------------------------------------------------------------
// Function: main		
// Description:	show case of Queue/CDLL
// Calls: All CDLL/Queue methods
// Throws: catches all exceptions
// History Log:
// https://github.com/qwergram/CS133Assignment/blame/master/Project2/main.cpp
// ------------------------------------------------------------------------
int main(void)
{
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

		PublicQueue<char> m = PublicQueue<char>(3, 'X');
		PublicQueue<char> * myqueue = &m;
		cout << "myqueue: " << *myqueue << endl;
		CDLL<char> m2 = PublicQueue<char>();
		CDLL<char> * myqueue2 = &m2;
		cout << "myqueue2: " << *myqueue2 << endl;
		CDLL<char> m3 = PublicQueue<char>(*myqueue);
		CDLL<char> * myqueue3 = &m3;
		cout << "myqueue3: " << *myqueue3 << endl;
		CDLL<char> m4 = PublicQueue<char>(myqueue->begin(), myqueue->end());
		CDLL<char> * myqueue4 = &m4;
		cout << "myqueue4: " << *myqueue4 << endl;
		char Y = 'Y', Z = 'Z';
		myqueue->push(Y);
		myqueue->push(Z);
		
		cout << myqueue->pop() << endl;
		*myqueue2 = *myqueue; // a copy
		cout << "myqueue: " << *myqueue << endl;
		// create a new iterator pointing to the beginning of mylist
		CDLL<char>::iterator queueit(myqueue->begin());
		cout << queueit++->data << " ";
		cout << queueit->data << endl;
		myqueue->release();
		cout << "myqueue: " << *myqueue << endl;
		cout << "myqueue2: " << *myqueue2 << endl;
		
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