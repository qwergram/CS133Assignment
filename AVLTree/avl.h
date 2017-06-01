#ifndef AVL_H
#define AVL_H

#include "bst.h"
using namespace std;
using namespace NP_BST;
namespace NP_AVL
{
	template<class T>
	class avl : public bst<T>
	{
	public:
		using bst<T>::bst;
		avl<T>& operator=(const avl<T> & t);
		avl<T>& operator=(const bst<T> & t);
		avl<T> operator+(const T d)
			{ avl<T> temp = *this; temp.insert(d); return temp; }
		bool insert(T d) { return insert(d, root); }
		bool insert(T d, node<T>* &cur);
		T popHigh(node<T>* &cur);
		T popFirstOf(const T& d) { return popFirstOf(d, root); }
		T popFirstOf(const T& d, node<T> *& np);
		~avl() { delTree(); }
	protected:
		T popNode(node<T>* &cur);
		node<T> * rotateRight(node<T> *nodeN);
		node<T> * rotateLeft(node<T> *nodeN);
		node<T> * rotateRightLeft(node<T> *nodeN);
		node<T> * rotateLeftRight(node<T> *nodeN);
		node<T> * rebalance(node<T> *& nodeN);
		int getHeightDifference(const node<T> *const nodeN) const;
	};


	template<class T>
	inline bool avl<T>::insert(T d, node<T>* &cur) {
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (isempty())
				root = cur;
			return true;
		}
		else if (!contains(d))
		{
			if (d < cur->value())
				insert(d, cur->left);
			else
				insert(d, cur->right);
			if (root != nullptr)
				root->setHeight();
			rebalance(cur);
			return true;
		}
		return false;
	}

	template<class T>
	inline T avl<T>::popNode(node<T>*& cur)
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
			node<T>* temp = cur->right;
			delete cur;
			cur = temp;
			rebalance(getroot());
		}
		else if (cur->right == nullptr)
		{ // only left child
			node<T>* temp = cur->left;
			delete cur;
			cur = temp;
			rebalance(getroot());
		}
		else
		{ // two children
			cur->setdata(popHigh(cur->left));
			rebalance(getroot());
			// pops leftmost node of right child and
			// places that value into the current node
		}
		if (root != nullptr)
			root->setHeight();
		return contents;
	}

	template<class T>
	inline T avl<T>::popHigh(node<T>*& cur)
	{
		if (cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if (cur->right == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->left;
			delete cur;
			cur = temptr;
			if (root != nullptr)
				root->setHeight();
			rebalance(cur);
			return temp;
		}
		return popHigh(cur->right);
	}

	template<class T>
	inline T avl<T>::popFirstOf(const T & d, node<T>*& np)
	{
		node<T>* matchptr = nullptr;
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

	template<class T>
	inline node<T> * avl<T>::rotateRight(node<T>* target)
	{
		node<T> * temp = target->right;
		target->right = temp->left;
		temp->left = target;
		return temp;
	}
	template<class T>
	inline node<T>* avl<T>::rotateLeft(node<T>* target)
	{
		node<T> * temp;
		temp = target->left;
		target->left = temp->right;
		temp->right = target;
		return temp;
	}
	template<class T>
	inline node<T>* avl<T>::rotateRightLeft(node<T>* target)
	{
		node<T> * temp;
		temp = target->right;
		target->right = rotateLeft(temp);
		return rotateRight(target);
	}
	template<class T>
	inline node<T>* avl<T>::rotateLeftRight(node<T>* target)
	{
		node<T> * temp;
		temp = target->left;
		target->left = rotateRight(temp);
		return rotateLeft(target);
	}

	template<class T>
	inline node<T>* avl<T>::rebalance(node<T> *& target)
	{
		int bal_factor = getHeightDifference(target);
		if (bal_factor > 1)
		{
			if (getHeightDifference(target->left) > 0)
				target = rotateLeft(target);
			else
				target = rotateLeftRight(target);
		}
		else if (bal_factor < -1)
		{
			if (getHeightDifference(target->right) > 0)
				target = rotateRightLeft(target);
			else
				target = rotateRight(target);
		}
		setHeight();
		return target;
	}

	template<class T>
	inline int avl<T>::getHeightDifference(const node<T> * const target) const
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
}
#endif