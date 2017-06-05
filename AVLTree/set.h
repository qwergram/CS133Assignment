#ifndef SET_H
#define SET_H
//-----------------------------------------------------------------------------
// Title: 
// Description: 
// Meta: 
// Programmer: 
//		Written by Paul Bladek
//		Modified by Norton Pengra
// Date: June 2017
// Version: 1.10
// Environment: 
//      Intel i7
//		Software: MS Windows 10 for execution;
//		Compiles under Microsoft Visual C++.Net 2017
// Classes:
//		class Node<T>:
//			A node containing a value, with two pointers
//			to a left and right child. Also holds a height
//			attribute.
//		
//		class Bst<T>:
//	!NEW!	Public Sub Classes:
//	!NEW!		BFIterator
//	!NEW!			Constructor(tree) -- creates a BF traversal iterator of given tree
//	!NEW!			next() -- returns the next node in BF traversal
//	!NEW!			endOfTree() -- returns True if BFT has reached the end
//	!NEW!			getLast() -- retrieve the last thing returned by next
//			Public Methods:
//				Constructors
//				getroot() -- used for retrieving root node
//				operator = overload -- used for reassigning trees
//				operator += overload -- used for adding trees with syntactic sugars
//					(can be used to add another T or another Bst<T>)
//				operator + overload -- used for adding trees with syntactic sugars
//				isempty() -- returns true of the tree contains no items
//	!NEW!		contains(T item) -- returns true if item is in tree
//				insert(T item) -- inserts item into tree
//				delTree() -- deletes entire tree
//				print() -- "pretty" prints the tree up to 7 layers
//				print ... () -- related methods for print
//				popNode(Node<T> *& t) -- pop the node t from the tree
//				popLow(Node<T> *& t) -- pop the leftmost child of node t
//				popHigh(Node<T> *& t) -- pop the rightmost child of node t
//				getHeight() -- get height of the tree
//				setHeight() -- recursively set the height attribute of each node.
//				setLevel -- related method for print
//				getNumberOfNodes -- get number of nodes in tree
//				destructor -- calls delTree
//			Protected Attributes:
//				Node<T> * root -- the root of the tree
//				Node<T> ** parentptr -- holding pointer needed by some functions
//				
// History Log:
//		revised June, 2017
//--------------------------------------------------------------------


#include "avl.h"
using namespace std;
using namespace NP_AVL;

namespace NP_SET
{
	template<class T>
	class Set : protected avl<T>
	{
	public:
		using avl<T>::avl;
		bool insert(T d) { return avl<T>::insert(d, this->root); }
		// print methods
		void print(ostream& out)const { this->print(this->root, out); }
		void print(Node<T>* cur, ostream& out) const;
		void printXlevel(ostream& out) const { this->printXlevel(this->root, out); }
		void printXlevel(Node<T>* cur, ostream& out) const;

		bool remove(T target);
		bool isMember(T target) { return this->contains(target); }
		Set<T> Union(Set<T> rhs);
		Set<T> intersection(Set<T> rhs);

		~Set() { this->delTree(); }

	protected:
		Node<T>* &getroot() { return this->root; }
	};

	//--------------------------------------------------------------------
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Returns: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline void Set<T>::print(Node<T>* cur, ostream & out) const
	{
		if (cur != nullptr)
		{
			print(cur->left, out);
			out << cur->value() << "(" << cur->getHeight() << ") ";
			print(cur->right, out);
		}
	}

	//--------------------------------------------------------------------
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Returns: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline void Set<T>::printXlevel(Node<T>* cur, ostream & out) const
	{
		if (cur == nullptr)
			return;
		const size_t SPACER = 64;
		const T NO_NODE = static_cast<T>(-1);
		const int PRINT_MAX = 6;
		vector<vector<T>> treeVector(cur->getHeight());

		for (int i = 0; i < cur->getHeight(); i++)
		{
			out << "level " << i + 1 << ": ";
			if (i < PRINT_MAX)
			{
				int size = static_cast<int>(pow(2.0, i));
				treeVector[i] = vector<T>(size, NO_NODE);
				setLevel(cur, treeVector[i], i);
				out << string(SPACER / (2 * size), ' ');
				for (int j = 0; j < static_cast<int>(treeVector[i].size());
					j++)
				{
					if (treeVector[i][j] != NO_NODE)
						out << treeVector[i][j];
					else
						out << ' ';
					out << string(SPACER / size - 1, ' ');
				}
			}
			else
				out << "  . . .";

			out << endl;
		}
	}

	//--------------------------------------------------------------------
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Returns: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline bool Set<T>::remove(T target)
	{
		try {
			this->popFirstOf(target);
		}
		catch (invalid_argument) {
			return false;
		}
		return true;
	}

	//--------------------------------------------------------------------
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Returns: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Set<T> Set<T>::Union(Set<T> rhs)
	{
		auto newTree = Set<T>(*this);
		newTree.addTree(rhs.getroot());
		return newTree;
	}

	//--------------------------------------------------------------------
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Returns: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Set<T> Set<T>::intersection(Set<T> rhs)
	{
		auto newTree = Set<T>();
		// Dear Future Norton:
		// The following line of code can be explained here:
		// https://travis-ci.org/qwergram/CS133Assignment/builds/239750741#L309
		// https://travis-ci.org/qwergram/CS133Assignment/builds/239752012
		// Also here:
		// https://github.com/qwergram/CS133Assignment/commit/8602ca33fc8357960ca269d0aa0aaf31b6bd5925
		// Please learn from this.
		// Much love,
		// Past Norton.
		auto lhsIterator = typename Set<T>::BFIterator(*this);

		while (!lhsIterator.endOfTree()) {
			auto thisNode = lhsIterator.next().value();
			if (rhs.isMember(thisNode))
				newTree.insert(thisNode);
		}

		return newTree;
	}

}
#endif
