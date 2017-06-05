#ifndef BST_H
#define BST_H
//-----------------------------------------------------------------------------
// Title: Binary Search Tree
// Description: A classic Binary Search Tree
// Meta: https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
// Programmer: 
//		Written by Paul Bladek
//		Modified by Norton Pengra
// Date: June 2017
// Version: 1.10
// Environment: Intel i7
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
//		December, 2000
//		revised April, 2005
//		revised May, 2008
//		revised May, 2012
//		revised June, 2013
//		revised June, 2017
//--------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>
#include <queue>

using namespace std;

namespace NP_BST
{
	//--------------------------------------------------------------------
	// BST NODE
	// REQUIRES Type T be able to convert from int & have < & == defined
	//--------------------------------------------------------------------
	template<class T>
	class Node
	{
	public:
		Node(T d = 1) : m_data(d), m_height(1), left(nullptr),
			right(nullptr) {}
		Node(const Node<T>& n); // Copy Constructor
		Node<T>& operator=(const Node<T>& n);
		T value() const { return m_data; }    // Accessor
		operator T() const { return m_data; }  // cast to data type
		void setdata(T d) { m_data = d; }
		int getHeight() const { return m_height; }
		int setHeight();
	private:
		T m_data;
		int m_height;
	public:  // to freely use these
		Node<T>* left;
		Node<T>* right;
	};

	//--------------------------------------------------------------------
	// COPY CONSTRUCTOR
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	Node<T>::Node(const Node<T>& n)
		: m_data(n.m_data), m_height(n.getHeight()), left(nullptr),
		right(nullptr)
	{
		if (n.left != nullptr)
			left = new Node<T>(*(n.left));
		if (n.right != nullptr)
			right = new Node<T>(*(n.right));
	}

	//--------------------------------------------------------------------
	// = operator
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	Node<T>& Node<T>::operator=(const Node<T>& n)  // overloaded =
	{
		if (this != &n)
		{
			m_data = n.m_data;
			m_height = n.getHeight();
			if (n.left != nullptr)
				left = new Node<T>(*(n.left));
			else
				left = nullptr;
			if (n.right != nullptr)
				right = new Node<T>(*(n.right));
			else
				right = nullptr;
		}
		return *this;
	}


	//--------------------------------------------------------------------
	// recursively sets the Height of the node
	//--------------------------------------------------------------------
	template <class T>
	int Node<T>::setHeight()
	{
		int lHeight = 0;
		int rHeight = 0;
		m_height = 1;

		if (left != nullptr)
			lHeight = left->setHeight();
		if (right != nullptr)
			rHeight = right->setHeight();
		return (m_height += (lHeight > rHeight) ? lHeight : rHeight);
	}

	//--------------------------------------------------------------------
	// Binary Search Tree -- Basic Implementation
	//--------------------------------------------------------------------
	template <class T>
	class Bst
	{
	public:
		class BFIterator { // NEW CLASS
		public:
			BFIterator(Bst<T> & tree) {
				if (!tree.isempty()) {
					oldQueue.push(*tree.getroot());
				}
			};
			const Node<T> next();
			const bool endOfTree() { return oldQueue.empty(); }
			const Node<T> getLast() { return this->lastPop; }
		protected:
			queue<Node<T>> oldQueue = queue<Node<T>>();
			Node<T> lastPop;
		};

		Bst() : root(nullptr), parentptr(&root) {}
		Bst(const Bst<T>& t) : root(nullptr), parentptr(&root)
		{
			if (t.root != nullptr) root = new Node<T>(*(t.root));
		}

		Node<T>* &getroot() { return root; }

		bool isempty() const { return (root == nullptr); }

		Bst<T>& operator=(const Bst<T>& t);
		Bst<T>& operator+=(const Bst<T>& t);
		Bst<T>& operator+=(const T d) { insert(d, root); return *this; }
		Bst<T> operator+(const T d) {
			Bst<T> temp = *this;
			temp.insert(d, temp.root); return temp;
		}
		bool contains(const T& item); // NEW
		void findFirstOf(const T& d, Node<T>* &np, Node<T>* &match);
		bool insert(T d);
		void delTree() { delTree(root); }
		void print(ostream& out)const { print(root, out); }
		void print(Node<T>* cur, ostream& out) const;
		void printXlevel(ostream& out) const { printXlevel(root, out); }
		void printXlevel(Node<T>* cur, ostream& out) const;
		T popNode(Node<T>* &cur);
		T popLow(Node<T>* &cur);
		T popHigh(Node<T>* &cur);
		T popFirstOf(const T& d) { return popFirstOf(d, root); }
		T popFirstOf(const T& d, Node<T>*& np);
		int getHeight() const
		{
			if (isempty()) return 0; return root->getHeight();
		}
		void setHeight() { if (root != nullptr) root->setHeight(); }

		void setLevel(Node<T>* cur, vector<T>& levelVector,
			int level2print, int position = 0) const;
		int getNumberOfNodes() const { return getNumberOfNodes(root); }
		int getNumberOfNodes(Node<T>* np) const;
		~Bst() { delTree(root); }
		void delTree(Node<T>* &cur);
	protected:
		bool insert(T d, Node<T>* &cur);
		Node<T>* root; // root of this tree
		Node<T>** parentptr; // holding pointer needed by some functions

		void addTree(const Node<T>* np); // used by +
	};

	//--------------------------------------------------------------------
	// overloaded =
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	Bst<T>& Bst<T>::operator=(const Bst<T>& t)
	{
		if (this != &t)
		{
			if (!isempty())
				delTree(root);
			if (!t.isempty())
			{
				root = new Node<T>(*(t.root));
			}
		}
		return *this;
	}

	//--------------------------------------------------------------------
	// overloaded +=
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	Bst<T>& Bst<T>::operator+=(const Bst<T>& t)
	{
		addTree(t.root);
		return *this;
	}

	//--------------------------------------------------------------------
	// recursively adds in the contents of a second tree
	//--------------------------------------------------------------------
	template <class T>
	void Bst<T>::addTree(const Node<T>* np)
	{
		if (np != nullptr)
		{
			addTree(np->left);
			addTree(np->right);
			insert(np->value(), root);
		}
	}

	template<class T>
	inline bool Bst<T>::contains(const T & item)
	{
		Node<T>* matchptr = nullptr;
		findFirstOf(item, getroot(), matchptr);
		return matchptr != nullptr;
	}

	//--------------------------------------------------------------------
	// recursively finds the first occurance of a data item
	// pre: match must be set to nullptr
	//--------------------------------------------------------------------
	template <class T>
	void Bst<T>::findFirstOf(const T& d, Node<T>* &np, Node<T>* &match)
	{
		if (match != nullptr)
			return;
		if (np != nullptr)
		{
			findFirstOf(d, np->left, match);
			if (d == np->value())
			{
				match = np;
				parentptr = &np;
				return;
			}
			findFirstOf(d, np->right, match);
		}
	}

	//--------------------------------------------------------------------
	// inserts a new element
	// into the tree
	//--------------------------------------------------------------------
	template <class T>
	bool Bst<T>::insert(T d)
	{
		return insert(d, root);
	}
	//--------------------------------------------------------------------
	// inserts a new element
	// into the tree
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	bool Bst<T>::insert(T d, Node<T>* &cur)
	{
		if (cur == nullptr)
		{
			cur = new Node<T>(d);
			if (isempty())
				root = cur;
			return true;
		} else if (!contains(d))
		{
			if (d < cur->value())
				insert(d, cur->left);
			else
				insert(d, cur->right);
			if (root != nullptr)
				root->setHeight();
			return true;
		}
		return false;
	}

	//-------------------------------------------------------------------- 
	// recursively prints out the tree inorder
	//--------------------------------------------------------------------
	template <class T>
	void Bst<T>::print(Node<T>* cur, ostream& out) const
	{
		if (cur != nullptr)
		{
			print(cur->left, out);
			out << cur->value() << "(" << cur->getHeight() << ") ";
			print(cur->right, out);
		}
	}

	//------------------------------------------------------------------------
	// recursuively sets levelVector to represent the specified level 
	//------------------------------------------------------------------------
	template <class T>
	void Bst<T>::setLevel(Node<T>* cur, vector<T>& levelVector,
		int level2print, int position) const
	{
		static int currentLevel = -1;
		if (level2print < 0)
			return;
		if (cur != nullptr)
		{
			currentLevel++;
			if (currentLevel < level2print)
				setLevel(cur->left, levelVector, level2print, position * 2);
			if (currentLevel == level2print)
				levelVector[position] = cur->value();
			if (currentLevel < level2print)
				setLevel(cur->right, levelVector, level2print,
					position * 2 + 1);
			currentLevel--;
		}
	}

	//------------------------------------------------------------------------ 
	// prints out the tree in level order
	// pre: -1 must be able to be cast to T
	//------------------------------------------------------------------------
	template <class T>
	void Bst<T>::printXlevel(Node<T>* cur, ostream& out) const
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
	// recursively deletes out the subtree
	//--------------------------------------------------------------------
	template <class T>
	void Bst<T>::delTree(Node<T>* &cur)
	{
		if (cur != nullptr)
		{
			delTree(cur->left);
			delTree(cur->right);
			delete cur;
			cur = nullptr;
			if (root != nullptr)
				root->setHeight();
		}
	}

	//-------------------------------------------------------------------- 
	// pops a given node
	//--------------------------------------------------------------------
	template <class T>
	T Bst<T>::popNode(Node<T>* &cur)
	{
		if (cur == nullptr)
			throw (invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if (cur->left == nullptr && cur->right == nullptr)
		{ // no children
			delete cur;
			cur = nullptr;
		}
		else if (cur->left == nullptr)
		{ // only right child
			Node<T>* temp = cur->right;
			delete cur;
			cur = temp;
		}
		else if (cur->right == nullptr)
		{ // only left child
			Node<T>* temp = cur->left;
			delete cur;
			cur = temp;
		}
		else
		{ // two children
			cur->setdata(popHigh(cur->left));
			// pops leftmost node of right child and
			// places that value into the current node
		}
		if (root != nullptr)
			root->setHeight();
		return contents;
	}

	//-------------------------------------------------------------------- 
	// pops out the leftmost child of cur
	// throws invalid_argument
	//--------------------------------------------------------------------
	template <class T>
	T Bst<T>::popLow(Node<T>* &cur)
	{
		if (cur == nullptr)
			throw (invalid_argument("Pointer does not point to a node"));
		if (cur->left == nullptr)
		{
			T temp = cur->value();
			Node<T>* temptr = cur->right;
			delete cur;
			cur = temptr;
			if (root != nullptr)
				root->setHeight();
			return temp;
		}
		return popLow(cur->left);
	}

	//------------------------------------------------------------------------
	// pops out the rightmost child of cur
	// throws invalid_argument
	//------------------------------------------------------------------------
	template <class T>
	T Bst<T>::popHigh(Node<T>* &cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->right == nullptr)
		{
			T temp = cur->value();
			Node<T>* temptr = cur->left;
			delete cur;
			cur = temptr;
			if (root != nullptr)
				root->setHeight();
			return temp;
		}
		return popHigh(cur->right);
	}

	//-------------------------------------------------------------------- 
	// pops first node matching d
	//--------------------------------------------------------------------
	template <class T>
	T Bst<T>::popFirstOf(const T& d, Node<T>*& np)
	{
		Node<T>* matchptr = nullptr;
		findFirstOf(d, np, matchptr);
		if (*parentptr != nullptr)
		{
			if ((*parentptr)->value() == d)
				return popNode((*parentptr));
		}
		if (root != nullptr)
			root->setHeight();
		return 0;
	}

	//-------------------------------------------------------------------- 
	// returns the number of nodes in the tree
	// recursive
	//--------------------------------------------------------------------
	template <class T>
	int Bst<T>::getNumberOfNodes(Node<T>* np) const
	{
		int count = 1;
		if (np != nullptr)
		{
			count += getNumberOfNodes(np->left);
			count += getNumberOfNodes(np->right);
			return count;
		}
		return 0;
	}

	//--------------------------------------------------------------------  
	// Overloaded << for bst<T>
	//--------------------------------------------------------------------
	template <class T>
	ostream& operator<<(ostream& out, Bst<T> tree)
	{
		tree.print(tree.getroot(), out);
		return out;
	}

	//--------------------------------------------------------------------
	// Title: BFIterator next method
	// Description: goes to next item in BFT
	// Called By: Set<T>::intersection
	// Calls: node::value()
	// Throws: out_of_range if next() called at end of tree
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline const Node<T> Bst<T>::BFIterator::next() {
		if (!oldQueue.empty()) {
			Node<T> lastNode = oldQueue.front();
			oldQueue.pop();
			if (lastNode.left != nullptr)
				oldQueue.push(*lastNode.left);
			if (lastNode.right != nullptr)
				oldQueue.push(*lastNode.right);
			this->lastPop = lastNode;
			return lastNode;
		}
		throw out_of_range("Reached end of tree");
	}

} // end namespace NP_BST

#endif