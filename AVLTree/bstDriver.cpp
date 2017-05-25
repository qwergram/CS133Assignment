#include <iostream>
#include <cstdlib>
#include "bst.h"
using namespace std;

//--------------------------------------------------------------------
// Test Driver for bst and node classes
// Compiled under MS Visual C++.Net 20013, Windows 7
// by Paul Bladek
// December, 2000
// revised April, 2005
// revised June, 2015
//--------------------------------------------------------------------
int main(void)
{
	using NP_BST::bst;
	using NP_BST::node;
	try
	{
		bst<char> tree;
		node<char>* marker = nullptr;
		char c;
		cout << "enter some characters, followed by <enter>.\n";
		do
		{
			cin.get(c);
			if (c == '\n')
				break;
			tree.insert(c);
		} while (true);
		//
		tree.printXlevel(cout);
		tree.popFirstOf('D', tree.getroot());

		tree.printXlevel(cout);
		//
		bst<char> tree2 = tree; // test overloaded =
		tree2 += tree; // test overloaded +
		cout << "tree 1:" << endl;
		cout << tree << " : " << tree.getNumberOfNodes()
			<< "nodes" << endl;  // test overloaded << and print()
		tree.printXlevel(cout);
		cout << endl << "tree 2:" << tree2
			<< tree.getNumberOfNodes() << "nodes" << endl;
		tree2.printXlevel(cout);
		cout << endl << endl << "Enter character to match: ";
		cin >> c;
		cout << tree.contains(c);

		// set marker to first match of c
		if (marker != nullptr)
			cout << marker->value();
		else
			cout << "not found";
		cout << "\n Enter character to delete: ";
		cin >> c;
		cin.ignore(FILENAME_MAX, '\n');
		c = tree.popFirstOf(c);

		// test popFirstOf(), popnode(), poplow()	
		cout << "<" << c << ">  " << tree << endl;
		tree.delTree();  // delete first tree
		tree2 += 'Z';     // add in another element , test +=
		tree2 = tree2 + 'Y';  // test +		
		cout << tree2 << endl;
		cout << "tree 1:" << endl;
		cout << tree << " : " << tree.getNumberOfNodes()
			<< "nodes" << endl;  // test overloaded << and print()
		tree.printXlevel(cout);
		cout << endl << "tree 2:" << tree2
			<< tree.getNumberOfNodes() << "nodes" << endl;
		tree2.printXlevel(cout);
		cout << endl;
		tree.delTree();  // delete second tree
	}
	catch (invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch (bad_alloc e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch (exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << "press \"Enter\" to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
}
