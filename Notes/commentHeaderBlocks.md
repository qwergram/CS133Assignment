# Example File Header Block
```cpp
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
```

# Blank Function/Method Header Block
```cpp
//--------------------------------------------------------------------
// Title: 
// Description: 
// Called By: 
// Calls: 
// Parameters: 
// Throws:
// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
//--------------------------------------------------------------------
```