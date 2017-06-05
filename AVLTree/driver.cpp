#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "avl.h"
#include "set.h"

using namespace NP_AVL;
using namespace NP_SET;

// == Set Tests == 
TEST_CASE("Set Test operations") {
	// test is a set with the tree structure:
	//		2
	//	3		1
	Set<int> test = Set<int>();
	test.insert(1);
	test.insert(2);
	test.insert(3);

	// test2 is a set with the tree structure:
	//		4
	//	5		3
	Set<int> test2 = Set<int>();
	test2.insert(3);
	test2.insert(4);
	test2.insert(5);

	// Make sure that 1, 2, 3 exist in test1 but not 4
	SECTION("Set isMember tests") {
		REQUIRE(test.isMember(1));
		REQUIRE(test.isMember(2));
		REQUIRE(test.isMember(3));
		REQUIRE_FALSE(test.isMember(4));
	}

	// Insert 4 and test isMember
	SECTION("Set isMember/Insertion tests") {
		test.insert(4);
		REQUIRE(test.isMember(4));
	}

	// Test unions
	SECTION("union tests") {
		// Esnure a union with itself
		// results in the same list
		SECTION("union self test") {
			auto test3 = test.Union(test);
			REQUIRE(test3.isMember(1));
			REQUIRE(test3.isMember(2));
			REQUIRE(test3.isMember(3));
		}

		// Ensure a union between {1, 2, 3}
		// and {3, 4, 5} results in 
		// {1, 2, 3, 4, 5} and has no effect
		// on existing trees.
		SECTION("union second tree test") {
			auto test3 = test.Union(test2);
			REQUIRE(test3.isMember(1));
			REQUIRE(test3.isMember(2));
			REQUIRE(test3.isMember(3));
			REQUIRE(test3.isMember(4));
			REQUIRE(test3.isMember(5));

			REQUIRE_FALSE(test.isMember(4));
			REQUIRE_FALSE(test.isMember(5));
			REQUIRE_FALSE(test2.isMember(1));
			REQUIRE_FALSE(test2.isMember(2));
		}

		// Ensure doing a union with an empty tree
		// doesn't break.
		SECTION("empty tree test") {
			auto test3 = test.Union(Set<int>());
			auto test4 = Set<int>();
			test4.Union(Set<int>());
			REQUIRE(test3.isMember(1));
			REQUIRE(test3.isMember(2));
			REQUIRE(test3.isMember(3));
		}
	}
	
	// Basic intersection test
	SECTION("Intersection tests") {
		
		// Ensure intersection between
		// {1, 2, 3} and {3, 4, 5}
		// results in {3}
		SECTION("Basic intersection") {
			auto test3 = test.intersection(test2);
			REQUIRE(test3.isMember(3));
			REQUIRE_FALSE(test3.isMember(1));
			REQUIRE_FALSE(test3.isMember(2));
			REQUIRE_FALSE(test3.isMember(4));
			REQUIRE_FALSE(test3.isMember(5));
		}

		// Ensure that calling intersection on
		// empty trees doesn't crash.
		SECTION("Empty intersection") {
			auto test3 = Set<int>();
			auto test4 = Set<int>();
			auto test5 = test3.intersection(test4);
		}

		// Ensure intersectiosn between two sets with
		// no identical elements returns empty tree
		SECTION("No intersection") {
			auto test3 = Set<int>();
			test3.insert(1);
			auto test4 = Set<int>();
			test4.insert(0);
			auto test5 = test3.intersection(test4);
			REQUIRE_FALSE(test5.isMember(0));
			REQUIRE_FALSE(test5.isMember(1));
		}
	}
}

TEST_CASE("Tree operation Overloads") {

	avl<int> test = avl<int>();
	for (int num : {
		50, 75, 25, 15, 60, 35, 100,
		10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	avl<int>test2 = avl<int>();
	for (int num : {
		5, 13, 16, 20, 27, 33, 40, 47,
		53, 57, 65, 73, 77, 90, 125, 200
	}) {
		test2.insert(num);
	}

	avl<int>test3 = avl<int>();
	test3.insert(5);

	SECTION("+= overload") {
		SECTION("Duplicate Items") {
			test2 += test3;

			REQUIRE(*test2.getroot() == 47);
			REQUIRE(*test2.getroot()->left == 20);
			REQUIRE(*test2.getroot()->right == 73);
			REQUIRE(*test2.getroot()->left->left == 13);
			REQUIRE(*test2.getroot()->left->right == 33);
			REQUIRE(*test2.getroot()->right->left == 57);
			REQUIRE(*test2.getroot()->right->right == 90);
			REQUIRE(*test2.getroot()->left->left->left == 5);
			REQUIRE(*test2.getroot()->left->left->right == 16);
			REQUIRE(*test2.getroot()->left->right->left == 27);
			REQUIRE(*test2.getroot()->left->right->right == 40);
			REQUIRE(*test2.getroot()->right->left->left == 53);
			REQUIRE(*test2.getroot()->right->left->right == 65);
			REQUIRE(*test2.getroot()->right->right->left == 77);
			REQUIRE(*test2.getroot()->right->right->right == 125);
		}

		SECTION("Mutually exclusive trees") {
			test += test2;

			REQUIRE(*test.getroot() == 50);
			REQUIRE(*test.getroot()->left == 25);
			REQUIRE(*test.getroot()->left->left == 15);
			REQUIRE(*test.getroot()->left->left->left == 10);
			REQUIRE(*test.getroot()->left->left->right == 17);
			REQUIRE(*test.getroot()->left->right == 35);
			REQUIRE(*test.getroot()->left->right->left == 30);
			REQUIRE(*test.getroot()->left->right->right == 45);
			REQUIRE(*test.getroot()->right == 75);
			REQUIRE(*test.getroot()->right->left == 60);
			REQUIRE(*test.getroot()->right->left->left == 55);
			REQUIRE(*test.getroot()->right->left->right == 70);
			REQUIRE(*test.getroot()->right->right == 100);
			REQUIRE(*test.getroot()->right->right->left == 80);
			REQUIRE(*test.getroot()->right->right->right == 150);
			REQUIRE(*test.getroot()->left->left->left->left == 5);
			REQUIRE(*test.getroot()->left->left->left->right == 13);
			REQUIRE(*test.getroot()->left->left->right->left == 16);
			REQUIRE(*test.getroot()->left->left->right->right == 20);
			REQUIRE(*test.getroot()->left->right->left->left == 27);
			REQUIRE(*test.getroot()->left->right->left->right == 33);
			REQUIRE(*test.getroot()->left->right->right->left == 40);
			REQUIRE(*test.getroot()->left->right->right->right == 47);
			REQUIRE(*test.getroot()->right->left->left->left == 53);
			REQUIRE(*test.getroot()->right->left->left->right == 57);
			REQUIRE(*test.getroot()->right->left->right->left == 65);
			REQUIRE(*test.getroot()->right->left->right->right == 73);
			REQUIRE(*test.getroot()->right->right->left->left == 77);
			REQUIRE(*test.getroot()->right->right->left->right == 90);
			REQUIRE(*test.getroot()->right->right->right->left == 125);
			REQUIRE(*test.getroot()->right->right->right->right == 200);
		}
	}

	SECTION("= overload") {
		test = test2;
		
		REQUIRE_FALSE(test.contains(50));
		REQUIRE_FALSE(test.contains(75));
		REQUIRE_FALSE(test.contains(25));
		REQUIRE_FALSE(test.contains(15));
		REQUIRE_FALSE(test.contains(60));
		REQUIRE_FALSE(test.contains(35));
		REQUIRE_FALSE(test.contains(100));
		REQUIRE_FALSE(test.contains(10));
		REQUIRE_FALSE(test.contains(30));
		REQUIRE_FALSE(test.contains(55));
		REQUIRE_FALSE(test.contains(80));
		REQUIRE_FALSE(test.contains(17));
		REQUIRE_FALSE(test.contains(45));
		REQUIRE_FALSE(test.contains(70));
		REQUIRE_FALSE(test.contains(150));

		REQUIRE(*test.getroot() == 47);
		REQUIRE(*test.getroot()->left == 20);
		REQUIRE(*test.getroot()->right == 73);
		REQUIRE(*test.getroot()->left->left == 13);
		REQUIRE(*test.getroot()->left->right == 33);
		REQUIRE(*test.getroot()->right->left == 57);
		REQUIRE(*test.getroot()->right->right == 90);
		REQUIRE(*test.getroot()->left->left->left == 5);
		REQUIRE(*test.getroot()->left->left->right == 16);
		REQUIRE(*test.getroot()->left->right->left == 27);
		REQUIRE(*test.getroot()->left->right->right == 40);
		REQUIRE(*test.getroot()->right->left->left == 53);
		REQUIRE(*test.getroot()->right->left->right == 65);
		REQUIRE(*test.getroot()->right->right->left == 77);
		REQUIRE(*test.getroot()->right->right->right == 125);

		REQUIRE(*test2.getroot() == 47);
		REQUIRE(*test2.getroot()->left == 20);
		REQUIRE(*test2.getroot()->right == 73);
		REQUIRE(*test2.getroot()->left->left == 13);
		REQUIRE(*test2.getroot()->left->right == 33);
		REQUIRE(*test2.getroot()->right->left == 57);
		REQUIRE(*test2.getroot()->right->right == 90);
		REQUIRE(*test2.getroot()->left->left->left == 5);
		REQUIRE(*test2.getroot()->left->left->right == 16);
		REQUIRE(*test2.getroot()->left->right->left == 27);
		REQUIRE(*test2.getroot()->left->right->right == 40);
		REQUIRE(*test2.getroot()->right->left->left == 53);
		REQUIRE(*test2.getroot()->right->left->right == 65);
		REQUIRE(*test2.getroot()->right->right->left == 77);
		REQUIRE(*test2.getroot()->right->right->right == 125);
	}

}

TEST_CASE("Breadth Traversal") {
	avl<int> test = avl<int>();
	for (int num : {
		50, 75, 25, 15, 60, 35, 100,
			10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	auto iterator = avl<int>::BFIterator(test);
	
	SECTION("forward iteration tests") {
		REQUIRE(iterator.next().value() == 50);
		REQUIRE(iterator.next().value() == 25);
		REQUIRE(iterator.next().value() == 75);
		REQUIRE(iterator.next().value() == 15);
		REQUIRE(iterator.next().value() == 35);
		REQUIRE(iterator.next().value() == 60);
		REQUIRE(iterator.next().value() == 100);
		REQUIRE(iterator.next().value() == 10);
		REQUIRE(iterator.next().value() == 17);
		REQUIRE(iterator.next().value() == 30);
		REQUIRE(iterator.next().value() == 45);
		REQUIRE(iterator.next().value() == 55);
		REQUIRE(iterator.next().value() == 70);
		REQUIRE(iterator.next().value() == 80);
		REQUIRE(iterator.next().value() == 150);
		REQUIRE_THROWS_WITH(iterator.next(), "Reached end of tree");
	}

	SECTION("getLast iteration tests") {
		iterator.next();
		REQUIRE(iterator.getLast().value() == 50);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 25);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 75);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 15);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 35);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 60);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 100);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 10);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 17);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 30);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 45);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 55);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 70);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 80);
		iterator.next();
		REQUIRE(iterator.getLast().value() == 150);
		REQUIRE_THROWS_WITH(iterator.next(), "Reached end of tree");
	}

}

TEST_CASE("Creating Large Trees") {
	avl<int> test = avl<int>();
	for (int num : {
		50, 75, 25, 15, 60, 35, 100,
			10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	SECTION("Tree with height of 4 tests") {
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	test.insert(5);
	test.insert(27);
	test.insert(53);
	test.insert(77);
	test.insert(13);
	test.insert(16);
	test.insert(20);
	test.insert(33);
	test.insert(40);
	test.insert(47);
	test.insert(57);
	test.insert(65);
	test.insert(73);
	test.insert(90);
	test.insert(125);
	test.insert(200);

	SECTION("Tree with height of 5 tests") {
		REQUIRE(test.getHeight() == 5);
		REQUIRE(test.getNumberOfNodes() == 31);

		REQUIRE(*test.getroot()->left->left->left->left == 5);
		REQUIRE(*test.getroot()->left->left->left->right == 13);
		REQUIRE(*test.getroot()->left->left->right->left == 16);
		REQUIRE(*test.getroot()->left->left->right->right == 20);
		REQUIRE(*test.getroot()->left->right->left->left == 27);
		REQUIRE(*test.getroot()->left->right->left->right == 33);
		REQUIRE(*test.getroot()->left->right->right->left == 40);
		REQUIRE(*test.getroot()->left->right->right->right == 47);
		REQUIRE(*test.getroot()->right->left->left->left == 53);
		REQUIRE(*test.getroot()->right->left->left->right == 57);
		REQUIRE(*test.getroot()->right->left->right->left == 65);
		REQUIRE(*test.getroot()->right->left->right->right == 73);
		REQUIRE(*test.getroot()->right->right->left->left == 77);
		REQUIRE(*test.getroot()->right->right->left->right == 90);
		REQUIRE(*test.getroot()->right->right->right->left == 125);
		REQUIRE(*test.getroot()->right->right->right->right == 200);
	}

}

TEST_CASE("deleting with balancing") {
	avl<int> test = avl<int>();
	
	SECTION("Sanity deletion tests") {
		test.insert(1);
		test.popFirstOf(1);
		REQUIRE_FALSE(test.contains(1));
	}

	SECTION("Delete empty tree") {
		REQUIRE_THROWS_WITH(test.popFirstOf(0), "Requested deleted item not found");
	}

	for (int num : {
		50, 75, 25, 15, 60, 35, 100,
		10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	SECTION("Delete non-existent nodes") {
		REQUIRE_THROWS_WITH(test.popFirstOf(1), "Requested deleted item not found");
	}

	SECTION("heavy deletion left side") {
		SECTION("scenario 1") {
			test.popFirstOf(25);
			test.popFirstOf(17);
			test.popFirstOf(15);

			REQUIRE(*test.getroot() == 50);
			REQUIRE(*test.getroot()->left == 35);
			REQUIRE(*test.getroot()->left->left == 10);
			REQUIRE(*test.getroot()->left->left->right == 30);
			REQUIRE(*test.getroot()->left->right == 45);
		}

		SECTION("scenario 2") {
			test.popFirstOf(35);
			test.popFirstOf(15);
			test.popFirstOf(50);

			REQUIRE(*test.getroot() == 45);
			REQUIRE(*test.getroot()->left == 25);
			REQUIRE(*test.getroot()->left->left == 10);
			REQUIRE(*test.getroot()->left->left->right == 17);
			REQUIRE(*test.getroot()->left->right == 30);
		}

		SECTION("scenario 3") {
			test.popFirstOf(35);
			test.popFirstOf(15);
			test.popFirstOf(50);
			test.popFirstOf(25);
			test.popFirstOf(17);
			test.popFirstOf(30);

			REQUIRE(*test.getroot() == 75);
			REQUIRE(*test.getroot()->left == 45);
			REQUIRE(*test.getroot()->left->left == 10);
			REQUIRE(*test.getroot()->left->right == 60);
			REQUIRE(*test.getroot()->left->right->left == 55);
			REQUIRE(*test.getroot()->left->right->right == 70);
			REQUIRE(*test.getroot()->right == 100);
			REQUIRE(*test.getroot()->right->right == 150);
			REQUIRE(*test.getroot()->right->left == 80);
		}
	}

	SECTION("heavy deletion right side") {
		SECTION("scenario 1") {
			test.popFirstOf(75);
			test.popFirstOf(70);
			test.popFirstOf(60);

			REQUIRE(*test.getroot() == 50);
			REQUIRE(*test.getroot()->right == 100);
			REQUIRE(*test.getroot()->right->right == 150);
			REQUIRE(*test.getroot()->right->left == 55);
			REQUIRE(*test.getroot()->right->left->right == 80);
		}

		SECTION("scenario 2") {
			test.popFirstOf(100);
			test.popFirstOf(60);
			test.popFirstOf(50);

			REQUIRE(*test.getroot() == 45);
			REQUIRE(*test.getroot()->right == 75);
			REQUIRE(*test.getroot()->right->right == 80);
			REQUIRE(*test.getroot()->right->right->right == 150);
			REQUIRE(*test.getroot()->right->left == 55);
			REQUIRE(*test.getroot()->right->left->right == 70);
			REQUIRE(*test.getroot()->left == 25);
			REQUIRE(*test.getroot()->left->left == 15);
			REQUIRE(*test.getroot()->left->right == 35);
			REQUIRE(*test.getroot()->left->right->left == 30);
			REQUIRE(*test.getroot()->left->left->left == 10);
			REQUIRE(*test.getroot()->left->left->right == 17);
		}

		SECTION("scenario 3") {
			test.popFirstOf(100);
			test.popFirstOf(60);
			test.popFirstOf(50);
			test.popFirstOf(75);
			test.popFirstOf(80);
			test.popFirstOf(70);

			REQUIRE(*test.getroot() == 45);
			REQUIRE(*test.getroot()->right == 55);
			REQUIRE(*test.getroot()->right->right == 150);
			REQUIRE(*test.getroot()->left == 25);
			REQUIRE(*test.getroot()->left->right == 35);
			REQUIRE(*test.getroot()->left->right->left == 30);
			REQUIRE(*test.getroot()->left->left == 15);
			REQUIRE(*test.getroot()->left->left->left == 10);
			REQUIRE(*test.getroot()->left->left->right == 17);

			test.popFirstOf(150);

			REQUIRE(*test.getroot() == 25);
			REQUIRE(*test.getroot()->left == 15);
			REQUIRE(*test.getroot()->left->left == 10);
			REQUIRE(*test.getroot()->left->right == 17);
			REQUIRE(*test.getroot()->right == 45);
			REQUIRE(*test.getroot()->right->right == 55);
			REQUIRE(*test.getroot()->right->left == 35);
			REQUIRE(*test.getroot()->right->left->left == 30);
		}
	}
}

TEST_CASE("Testing deleting without balancing") {
	avl<int> test = avl<int>();
	for (int num : {
		50, 75, 25, 15, 60, 35, 100, 
		10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	REQUIRE(*test.getroot() == 50);
	REQUIRE(*test.getroot()->left == 25);
	REQUIRE(*test.getroot()->left->left == 15);
	REQUIRE(*test.getroot()->left->left->left == 10);
	REQUIRE(*test.getroot()->left->left->right == 17);
	REQUIRE(*test.getroot()->left->right == 35);
	REQUIRE(*test.getroot()->left->right->left == 30);
	REQUIRE(*test.getroot()->left->right->right == 45);
	REQUIRE(*test.getroot()->right == 75);
	REQUIRE(*test.getroot()->right->left == 60);
	REQUIRE(*test.getroot()->right->left->left == 55);
	REQUIRE(*test.getroot()->right->left->right == 70);
	REQUIRE(*test.getroot()->right->right == 100);
	REQUIRE(*test.getroot()->right->right->left == 80);
	REQUIRE(*test.getroot()->right->right->right == 150);

	SECTION("pop 10") {
		test.popFirstOf(10);
		REQUIRE(*test.getroot() == 50);
		REQUIRE((*test.getroot()->left) == 25);
		REQUIRE((*test.getroot()->left->left) == 15);
		REQUIRE(test.getroot()->left->left->left == nullptr);
		REQUIRE((*test.getroot()->left->left->right) == 17);
		REQUIRE((*test.getroot()->left->right) == 35);
		REQUIRE((*test.getroot()->left->right->left) == 30);
		REQUIRE((*test.getroot()->left->right->right) == 45);
		REQUIRE((*test.getroot()->right) == 75);
		REQUIRE((*test.getroot()->right->left) == 60);
		REQUIRE((*test.getroot()->right->left->left) == 55);
		REQUIRE((*test.getroot()->right->left->right) == 70);
		REQUIRE((*test.getroot()->right->right) == 100);
		REQUIRE((*test.getroot()->right->right->left) == 80);
		REQUIRE((*test.getroot()->right->right->right) == 150);
	}

	SECTION("pop 17") {
		test.popFirstOf(17);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(test.getroot()->left->left->right == nullptr);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 30") {
		test.popFirstOf(30);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(test.getroot()->left->right->left == nullptr);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 45") {
		test.popFirstOf(45);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(test.getroot()->left->right->right == nullptr);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 55") {
		test.popFirstOf(55);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(test.getroot()->right->left->left == nullptr);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 70") {
		test.popFirstOf(70);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(test.getroot()->right->left->right == nullptr);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 80") {
		test.popFirstOf(80);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(test.getroot()->right->right->left == nullptr);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 150") {
		test.popFirstOf(150);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(test.getroot()->right->right->right == nullptr);
	}

	SECTION("pop 15") {
		test.popFirstOf(15);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 10);
		REQUIRE(test.getroot()->left->left->left == nullptr);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 35") {
		test.popFirstOf(35);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 30);
		REQUIRE(test.getroot()->left->right->left == nullptr);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 60") {
		test.popFirstOf(60);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 55);
		REQUIRE(test.getroot()->right->left->left == nullptr);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 100") {
		test.popFirstOf(100);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 80);
		REQUIRE(test.getroot()->right->right->left == nullptr);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 25") {
		test.popFirstOf(25);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 17);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(test.getroot()->left->left->right == nullptr);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 75") {
		test.popFirstOf(75);
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right == 70);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(test.getroot()->right->left->right == nullptr);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}

	SECTION("pop 50") {
		test.popFirstOf(50);
		REQUIRE(*test.getroot() == 45);
		REQUIRE(*test.getroot()->left == 25);
		REQUIRE(*test.getroot()->left->left == 15);
		REQUIRE(*test.getroot()->left->left->left == 10);
		REQUIRE(*test.getroot()->left->left->right == 17);
		REQUIRE(*test.getroot()->left->right == 35);
		REQUIRE(*test.getroot()->left->right->left == 30);
		REQUIRE(test.getroot()->left->right->right == nullptr);
		REQUIRE(*test.getroot()->right == 75);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->left->right == 70);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->right->left == 80);
		REQUIRE(*test.getroot()->right->right->right == 150);
	}
}

TEST_CASE("Testing inserting and balances") {
	avl<int> test = avl<int>();
	
	

	SECTION("empty tree sanity test") {
		REQUIRE(test.getHeight() == 0);
		REQUIRE(test.getNumberOfNodes() == 0);
	}

	SECTION("adding one item") {
		test.insert(50);
		REQUIRE(test.getNumberOfNodes() == 1);
		REQUIRE(test.getHeight() == 1);
	}
	
	SECTION("adding more items and check height/node count without balancing") {
		test.insert(50);
		test.insert(75);
		REQUIRE(test.getNumberOfNodes() == 2);
		REQUIRE(test.getHeight() == 2);
		
		test.insert(25);
		REQUIRE(test.getNumberOfNodes() == 3);
		REQUIRE(test.getHeight() == 2);

		test.insert(15);
		REQUIRE(test.getNumberOfNodes() == 4);
		REQUIRE(test.getHeight() == 3);

		test.insert(60);
		REQUIRE(test.getNumberOfNodes() == 5);
		REQUIRE(test.getHeight() == 3);

		test.insert(35);
		REQUIRE(test.getNumberOfNodes() == 6);
		REQUIRE(test.getHeight() == 3);

		test.insert(100);
		REQUIRE(test.getNumberOfNodes() == 7);
		REQUIRE(test.getHeight() == 3);

		test.insert(10);
		REQUIRE(test.getNumberOfNodes() == 8);
		REQUIRE(test.getHeight() == 4);

		test.insert(30);
		REQUIRE(test.getNumberOfNodes() == 9);
		REQUIRE(test.getHeight() == 4);

		test.insert(55);
		REQUIRE(test.getNumberOfNodes() == 10);
		REQUIRE(test.getHeight() == 4);

		test.insert(80);
		REQUIRE(test.getNumberOfNodes() == 11);
		REQUIRE(test.getHeight() == 4);

		test.insert(17);
		REQUIRE(test.getNumberOfNodes() == 12);
		REQUIRE(test.getHeight() == 4);

		test.insert(45);
		REQUIRE(test.getNumberOfNodes() == 13);
		REQUIRE(test.getHeight() == 4);

		test.insert(70);
		REQUIRE(test.getNumberOfNodes() == 14);
		REQUIRE(test.getHeight() == 4);

		test.insert(150);
		REQUIRE(test.getNumberOfNodes() == 15);
		REQUIRE(test.getHeight() == 4);
	}

	SECTION("test insert and right balancing") {
		test.insert(50);
		test.insert(75);
		test.insert(150);
		REQUIRE(test.getNumberOfNodes() == 3);
		REQUIRE(test.getHeight() == 2);
		REQUIRE(*(test.getroot()) == 75);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 150);
	}

	SECTION("test insert and left balancing") {
		test.insert(150);
		test.insert(75);
		test.insert(50);
		REQUIRE(test.getNumberOfNodes() == 3);
		REQUIRE(test.getHeight() == 2);
		REQUIRE(*(test.getroot()) == 75);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 150);
	}

	SECTION("test insert and secondary right tree formation") {
		/*
			Given the input 50, 75, 150, 200, 250
			This AVL takes it a step further, resulting in the following
			tree:
					75
				50		200
					  150  250
		*/
		test.insert(50);
		test.insert(75);
		test.insert(150);

		test.insert(200);
		REQUIRE(test.getNumberOfNodes() == 4);
		REQUIRE(test.getHeight() == 3);
		REQUIRE(*(test.getroot()) == 75);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 150);
		REQUIRE(*(test.getroot()->right->right) == 200);
		
		test.insert(250);
		REQUIRE(test.getNumberOfNodes() == 5);
		REQUIRE(test.getHeight() == 3);
		REQUIRE(*(test.getroot()) == 75);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 200);
		REQUIRE(*(test.getroot()->right->right) == 250);
		REQUIRE(*(test.getroot()->right->left) == 150);
	}

	SECTION("test insert and secondary left tree formation") {
		/*
		Given the input 250, 200, 150, 75, 50
		
		This AVL takes it a step further, resulting in the following
		tree:
				200
			75		250
		  50  150
		*/
		test.insert(250);
		test.insert(200);
		test.insert(150);

		test.insert(75);
		REQUIRE(test.getNumberOfNodes() == 4);
		REQUIRE(test.getHeight() == 3);
		REQUIRE(*(test.getroot()) == 200);
		REQUIRE(*(test.getroot()->left) == 150);
		REQUIRE(*(test.getroot()->right) == 250);
		REQUIRE(*(test.getroot()->left->left) == 75);

		test.insert(50);
		REQUIRE(test.getNumberOfNodes() == 5);
		REQUIRE(test.getHeight() == 3);
		REQUIRE(*(test.getroot()) == 200);
		REQUIRE(*(test.getroot()->left) == 75);
		REQUIRE(*(test.getroot()->right) == 250);
		REQUIRE(*(test.getroot()->left->left) == 50);
		REQUIRE(*(test.getroot()->left->right) == 150);
	}

	SECTION("test insert zig-zag on right side") {
		/*
			Given the input 50, 75, 60
			The AVL tree should output
					60
				50		75
					   
		*/
		test.insert(50);
		test.insert(75);
		test.insert(60);

		REQUIRE(test.getHeight() == 2);
		REQUIRE(test.getNumberOfNodes() == 3);

		REQUIRE(*(test.getroot()) == 60);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 75);
	}

	SECTION("test insert zig-zag on left side") {
		/*
		Given the input 60, 50, 75
		The AVL tree should output
				60
			50		75

		*/
		test.insert(60);
		test.insert(50);
		test.insert(75);

		REQUIRE(test.getHeight() == 2);
		REQUIRE(test.getNumberOfNodes() == 3);

		REQUIRE(*(test.getroot()) == 60);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 75);
	}

	SECTION("test insert heavy zig-zag on right side") {
		/*
		Given the input 50, 75, 60, 70
		The AVL tree should output
			60
		50		75
		       70

		*/
		test.insert(50);
		test.insert(75);
		test.insert(60);
		test.insert(70);


		REQUIRE(test.getHeight() == 3);
		REQUIRE(test.getNumberOfNodes() == 4);

		REQUIRE(*(test.getroot()) == 60);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 75);
		REQUIRE(*(test.getroot()->right->left) == 70);

		test.insert(65);

		REQUIRE(test.getHeight() == 3);
		REQUIRE(test.getNumberOfNodes() == 5);

		REQUIRE(*(test.getroot()) == 60);
		REQUIRE(*(test.getroot()->left) == 50);
		REQUIRE(*(test.getroot()->right) == 70);
		REQUIRE(*(test.getroot()->right->left) == 65);
		REQUIRE(*(test.getroot()->right->right) == 75);
	}

	SECTION("test insert heavy zig-zag on left side") {
		/*
		Given the input 50, 25, 35, 30, 32
		The AVL tree should output
					35
				30		50
			  25  32

		*/
		test.insert(50);
		test.insert(25);
		test.insert(35);
		test.insert(30);


		REQUIRE(test.getHeight() == 3);
		REQUIRE(test.getNumberOfNodes() == 4);

		REQUIRE(*(test.getroot()) == 35);
		REQUIRE(*(test.getroot()->left) == 25);
		REQUIRE(*(test.getroot()->right) == 50);
		REQUIRE(*(test.getroot()->left->right) == 30);

		test.insert(32);

		REQUIRE(test.getHeight() == 3);
		REQUIRE(test.getNumberOfNodes() == 5);

		REQUIRE(*(test.getroot()) == 35);
		REQUIRE(*(test.getroot()->left) == 30);
		REQUIRE(*(test.getroot()->right) == 50);
		REQUIRE(*(test.getroot()->left->left) == 25);
		REQUIRE(*(test.getroot()->left->right) == 32);
	}

	SECTION("Random insertion tests") {
		for (int num : {
			5, 13, 16, 20, 27, 33, 40, 47,
				53, 57, 65, 73, 77, 90, 125, 200
		}) {
			test.insert(num);
		}

		REQUIRE(*test.getroot() == 47);
		REQUIRE(*test.getroot()->left == 20);
		REQUIRE(*test.getroot()->right == 73);
		REQUIRE(*test.getroot()->left->left == 13);
		REQUIRE(*test.getroot()->left->right == 33);
		REQUIRE(*test.getroot()->right->left == 57);
		REQUIRE(*test.getroot()->right->right == 90);
		REQUIRE(*test.getroot()->left->left->left == 5);
		REQUIRE(*test.getroot()->left->left->right == 16);
		REQUIRE(*test.getroot()->left->right->left == 27);
		REQUIRE(*test.getroot()->left->right->right == 40);
		REQUIRE(*test.getroot()->right->left->left == 53);
		REQUIRE(*test.getroot()->right->left->right == 65);
		REQUIRE(*test.getroot()->right->right->left == 77);
		REQUIRE(*test.getroot()->right->right->right == 125);

	}
	
}

