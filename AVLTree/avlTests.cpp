#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "avl.h"

using namespace NP_AVL;

TEST_CASE("Parent and Child class operations") {
	avl<int> test = avl<int>();
	for (int num : {
		50, 75, 25, 15, 60, 35, 100,
			10, 30, 55, 80, 17, 45, 70, 150
	}) {
		test.insert(num);
	}

	bst<int>test2 = bst<int>();
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

