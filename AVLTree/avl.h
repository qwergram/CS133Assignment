#ifndef AVL_H
#define AVL_H

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

	template<class T>
	inline bool avl<T>::insert(T d, Node<T>* &cur) {
		if (cur == nullptr)
		{
			cur = new Node<T>(d);
			if (this->isempty())
				this->root = cur;
			return true;
		}
		if (d < cur->value())
			insert(d, cur->left);
		else if (d > cur->value())
			insert(d, cur->right);
		else
			return false;
		if (this->root != nullptr)
			this->root->setHeight();
		rebalance(cur);
		return true;
	}

	template<class T>
	inline T avl<T>::popFirstOf(const T & d, Node<T>*& np)
	{
		T val = (T)0;
		if (np != nullptr) {
			if (np->value() == d)
				val = this->popNode(np);
			else if (d < np->value())
				val = this->popFirstOf(d, np->left);
			else
				val = this->popFirstOf(d, np->right);
			rebalance(np);
		} else {
			throw invalid_argument("Requested deleted item not found");
		}
		return val;
	}

	template<class T>
	inline Node<T> * avl<T>::rotateRight(Node<T>* target)
	{
		Node<T> * temp = target->right;
		target->right = temp->left;
		temp->left = target;
		return temp;
	}

	template<class T>
	inline Node<T>* avl<T>::rotateLeft(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->left;
		target->left = temp->right;
		temp->right = target;
		return temp;
	}

	template<class T>
	inline Node<T>* avl<T>::rotateRightLeft(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->right;
		target->right = rotateLeft(temp);
		return rotateRight(target);
	}

	template<class T>
	inline Node<T>* avl<T>::rotateLeftRight(Node<T>* target)
	{
		Node<T> * temp;
		temp = target->left;
		target->left = rotateRight(temp);
		return rotateLeft(target);
	}

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
}
#endif