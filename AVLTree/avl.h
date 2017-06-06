#ifndef AVL_H
#define AVL_H
//-----------------------------------------------------------------------------
// Title: AVL Tree
// Description: A self-balancing AVL tree
// Meta: https://en.wikipedia.org/wiki/Tree_rotation
// Programmer: 
//		Written by Norton Pengra
// Date: June 2017
// Version: 1.10
// Environment: 
//      Intel i7
//		Software: MS Windows 10 for execution;
//		Compiles under Microsoft Visual C++.Net 2017
// Classes:
//		class avl<T> (public inheritance from bst)
//			Public Methods:
//				Inheritance of all BST Constructors
//				insert() -- synonymous to BST::insert
//				popFirstOf -- synonymous to BST::popFirstOf
//				destructor -- synonymous to BST::destructors
//			Protected Methods:
//				rotateRight -- fix right heavy imbalance
//				rotateLeft -- fix left heavy imbalance
//				rotateRightLeft -- fix right heavy imbalance
//				rotateLeftRight -- fix left heavy imbalance
//				getHeightDifference -- find imbalance and on what side
//				
// History Log:
//		https://github.com/qwergram/CS133Assignment/commits/project3
//--------------------------------------------------------------------

#include "bst.h"

using namespace std;
using namespace NP_BST;

namespace NP_AVL
{
	template<class T>
	class avl : public Bst<T>
	{
	public:
		using Bst<T>::Bst;
		bool insert(T d) { return insert(d, this->root); }
		bool insert(T d, Node<T>* &cur);
		T popFirstOf(const T& d) { return popFirstOf(d, this->root); }
		T popFirstOf(const T& d, Node<T> *& np);
		~avl() { this->delTree(); }
	protected:
		Node<T> * rotateRight(Node<T> *nodeN);
		Node<T> * rotateLeft(Node<T> *nodeN);
		Node<T> * rotateRightLeft(Node<T> *nodeN);
		Node<T> * rotateLeftRight(Node<T> *nodeN);
		Node<T> * rebalance(Node<T> *& nodeN);
		int getHeightDifference(const Node<T> *const nodeN) const;
	};

	//--------------------------------------------------------------------
	// Title: AVL::insert
	// Description: insert data at node target and rebalance
	//				will return false and refuse to insert if data
	//				already in tree.
	// Called By: drivers
	// Calls: isempty, insert, node constructor, rebalance
	// Parameters: data to insert, node target to insert into
	// Returns: true if insert succeeded
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline bool avl<T>::insert(T data, Node<T>* &target) {
		if (target == nullptr)
		{
			target = new Node<T>(data);
			if (this->isempty())
				this->root = target;
			return true;
		}
		if (data < target->value())
			insert(data, target->left);
		else if (data > target->value())
			insert(data, target->right);
		else
			return false;
		if (this->root != nullptr)
			this->root->setHeight();
		rebalance(target);
		return true;
	}

	//--------------------------------------------------------------------
	// Title: AVL::popFirstOf
	// Description: removes data specified from target node
	// Called By: drivers
	// Calls: popNode, popFirstOf, rebalance
	// Parameters: data to remove, target to remove data from
	// Returns: data removed from tree on success and T(0) otherwise
	// Throws: invalid_argument if data not found
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline T avl<T>::popFirstOf(const T & data, Node<T> *& target)
	{
		T val = T(0);
		if (target != nullptr) {
			if (target->value() == data)
				val = this->popNode(target);
			else if (data < target->value())
				val = this->popFirstOf(data, target->left);
			else
				val = this->popFirstOf(data, target->right);
			rebalance(target);
		} else {
			throw invalid_argument("Requested deleted item not found");
		}
		return val;
	}

	//--------------------------------------------------------------------
	// Title: AVL::rotateRight
	// Description: rotate "against" heavy right side
	// Called By: rebalance
	// Calls: node copy constructor
	// Parameters: target to rotate
	// Returns: the new target
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T> * avl<T>::rotateRight(Node<T> * target)
	{
		Node<T> * temp = target->right;
		target->right = temp->left;
		temp->left = target;
		return temp;
	}

	//--------------------------------------------------------------------
	// Title: AVL::rotateLeft
	// Description: rotate "against" heavy leftt side
	// Called By: rebalance
	// Calls: node copy constructor
	// Parameters: target to rotate
	// Returns: the new target
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T>* avl<T>::rotateLeft(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->left;
		target->left = temp->right;
		temp->right = target;
		return temp;
	}

	//--------------------------------------------------------------------
	// Title: AVL::rotateRightLeft
	// Description: rotate "against" heavy right side (zig zag motion)
	// Called By: rebalance
	// Calls: node copy constructor, rotateLeft
	// Parameters: target to rotate
	// Returns: the new target
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T>* avl<T>::rotateRightLeft(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->right;
		target->right = rotateLeft(temp);
		return rotateRight(target);
	}

	//--------------------------------------------------------------------
	// Title: AVL::rotateLeftRight
	// Description: rotate "against" heavy leftt side (zig zag motion)
	// Called By: rebalance
	// Calls: node copy constructor, rotateRight
	// Parameters: target to rotate
	// Returns: the new target
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T>* avl<T>::rotateLeftRight(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->left;
		target->left = rotateRight(temp);
		return rotateLeft(target);
	}

	//--------------------------------------------------------------------
	// Title: AVL::rebalance
	// Description: rebalance the target (not recursive)
	// Called By: insert, popFirstOf
	// Calls: getHeightDifference, all rotates, setHeight
	// Parameters: target node to rotate
	// Returns: target after balance and rotations
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T>* avl<T>::rebalance(Node<T> *& target)
	{
		int bal_factor = getHeightDifference(target);
		if (bal_factor > 1)
		{
			if (getHeightDifference(target->left) < 0)
				target = rotateLeftRight(target);
			else
				target = rotateLeft(target);
		}
		else if (bal_factor < -1)
		{
			if (getHeightDifference(target->right) > 0)
				target = rotateRightLeft(target);
			else
				target = rotateRight(target);
		}
		this->setHeight();
		return target;
	}

	//--------------------------------------------------------------------
	// Title: AVL::getHeightDifference
	// Description: returns number representing balance of trees
	// Called By: rebalance
	// Calls: getHeight
	// Parameters: target to check balance of
	// Returns: positive number if left side heavier, 
	//			negative number if right side heavier
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/avl.h
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline int avl<T>::getHeightDifference(const Node<T> * const target) const
	{
		if (target != nullptr) {
			int left = 0;
			int right = 0;
			if (target->left != nullptr)
				left = target->left->getHeight();
			if (target->right != nullptr)
				right = target->right->getHeight();
			return left - right;
		}
		return 0;
	}
} // /NP_AVL
#endif