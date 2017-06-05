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
	// Called By: drivers
	// Calls: isempty, insert, node constructor
	// Parameters: data to insert, node target to insert into
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
	// Description: removes item 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline T avl<T>::popFirstOf(const T & data, Node<T>*& target)
	{
		T val = (T)0;
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
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
	// Test Plan: https://travis-ci.org/qwergram/CS133Assignment/
	//--------------------------------------------------------------------
	template<class T>
	inline Node<T> * avl<T>::rotateRight(Node<T>* target)
	{
		Node<T> * temp = target->right;
		target->right = temp->left;
		temp->left = target;
		return temp;
	}

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
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
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
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
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
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
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
	// Title: 
	// Description: 
	// Called By: 
	// Calls: 
	// Parameters: 
	// Throws:
	// History Log: https://github.com/qwergram/CS133Assignment/blame/project3/AVLTree/
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