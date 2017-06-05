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
		Set<T> intersection(Set<T> rhs);

		~Set() { this->delTree(); }

	protected:
		node<T>* &getroot() { return this->root; }
	};

	

	template<class T>
	inline void Set<T>::print(node<T>* cur, ostream & out) const
	{
		if (cur != nullptr)
		{
			print(cur->left, out);
			out << cur->value() << "(" << cur->getHeight() << ") ";
			print(cur->right, out);
		}
	}

	template<class T>
	inline void Set<T>::printXlevel(node<T>* cur, ostream & out) const
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
	inline Set<T> Set<T>::intersection(Set<T> rhs)
	{
		auto newTree = Set<T>();
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
