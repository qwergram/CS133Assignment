#ifndef SET_H
#define SET_H

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
		void print(node<T>* cur, ostream& out) const;
		void printXlevel(ostream& out) const { this->printXlevel(this->root, out); }
		void printXlevel(node<T>* cur, ostream& out) const;

		bool remove(T target);
		bool isMember(T target) { return this->contains(target); }
		Set<T> Union(Set<T> rhs);
		Set<T> intersection(Set<T> rhs, Node<T> * target = this->getroot());

		~Set() { this->delTree(); }
	
		

	protected:
		node<T>* &getroot() { return this->root; }
	private:
		Set<T> copyCat;
	};

	

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

	template<class T>
	inline Set<T> Set<T>::Union(Set<T> rhs)
	{
		auto newTree = Set<T>(*this);
		newTree.addTree(rhs.getroot());
		return newTree;
	}

	template<class T>
	inline Set<T> Set<T>::intersection(Set<T> rhs, Node<T>* target)
	{
		if (target == nullptr)

		return newTree;
	}

}
#endif
