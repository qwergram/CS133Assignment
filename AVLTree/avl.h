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
		bool insert(T d) { return insert(d, root); }
		bool insert(T d, node<T>* &cur);
		T popFirstOf(const T& d) { return popFirstOf(d, root); }
		T popFirstOf(const T& d, node<T> *& np);
		~avl() { delTree(); }
	protected:
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
	inline T avl<T>::popFirstOf(const T & d, node<T>*& np)
	{
		T val = NULL;
		if (np != nullptr) {
			if (np->value() == d)
				val = popNode(np);
			else if (d < np->value())
				val = popFirstOf(d, np->left);
			else
				val = popFirstOf(d, np->right);
			rebalance(np);
		} else {
			throw invalid_argument("Requested deleted item not found");
		}
		return val;
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