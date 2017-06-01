#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "avl.h"

using namespace NP_AVL;

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

	SECTION("test insert heavy zig-zag on right side") {
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

	
}

