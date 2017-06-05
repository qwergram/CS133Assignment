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
//		class set<T> (protected inheritance from avl)
//			Public Methods:
//				Inheritance of all AVL Constructors
//				print ... () -- synonymous to BST::print ... 
//				remove() -- synonymous to AVL::popFirstOf
//				insert() -- synonymous to AVL::insert
//				isMember() -- synonymous to BST::contains
//				Union() -- return a new tree with this tree ∪ new tree
//				intersection() -- return a new tree with this tree ∩ new tree
//				destructor -- synonymous to BST::destructors
//			Protected Methods:
//				getroot() -- synonymous to BST::getroot
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
	// Title: Set::print
	// Description: recursively prints out the tree inorder
	// Calls: print (self)
	// Parameters: the target node to print and stream to print to
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/set.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline void Set<T>::print(Node<T>* target, ostream & sout) const
	{
		if (target != nullptr)
		{
			print(target->left, sout);
			sout << target->value() << "(" << target->getHeight() << ") ";
			print(target->right, sout);
		}
	}

	//--------------------------------------------------------------------
	// Title: Set::printXLevel
	// Description: prints out the tree in level order
	// Calls: getHeight
	// Parameters: target node to start with and stream to print to
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/set.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline void Set<T>::printXlevel(Node<T>* target, ostream & sout) const
	{
		if (target == nullptr)
			return;
		const size_t SPACER = 64;
		const T NO_NODE = static_cast<T>(-1);
		const int PRINT_MAX = 6;
		vector<vector<T>> treeVector(target->getHeight());

		for (int i = 0; i < target->getHeight(); i++)
		{
			sout << "level " << i + 1 << ": ";
			if (i < PRINT_MAX)
			{
				int size = static_cast<int>(pow(2.0, i));
				treeVector[i] = vector<T>(size, NO_NODE);
				setLevel(target, treeVector[i], i);
				sout << string(SPACER / (2 * size), ' ');
				for (int j = 0; j < static_cast<int>(treeVector[i].size());
					j++)
				{
					if (treeVector[i][j] != NO_NODE)
						sout << treeVector[i][j];
					else
						sout << ' ';
					sout << string(SPACER / size - 1, ' ');
				}
			}
			else
				sout << "  . . .";

			sout << endl;
		}
	}

	//--------------------------------------------------------------------
	// Title: Set::remove
	// Description: removes target from tree
	// Called By: driver
	// Calls: popFirstOf
	// Parameters: target to remove
	// Returns: true on success
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/set.h
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
	// Title: Set::union
	// Description: returns a newtree with this tree conjoined to another
	//				tree.
	// Called By: driver
	// Calls: addTree, Set constructors
	// Parameters: right hand side tree to combine to self with
	// Returns: new tree with the combined trees
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/set.h
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
	// Title: Set::intersection
	// Description: returns mathematical intersection with this tree
	//				and another tree.
	// Called By: driver
	// Calls: iterator constructor, iterator::next, insert
	// Parameters: right hand side tree to intersect with
	// Returns: new tree with items that intersect
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/set.h
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
