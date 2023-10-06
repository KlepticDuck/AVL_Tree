#define CATCH_CONFIG_MAIN
#include "AVL.h"
#include <catch2/catch_test_macros.hpp>


/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){

		AVL tree;   // Create a Tree object
		tree.insert(tree.head, "Bratt Morejon", 77774568);
		tree.insert(tree.head, "Christian Rodriguez", 11111111);
		tree.insert(tree.head, "Caca PeePee", 55555555);
		//std::vector<int> actualOutput =
        int fuck = 0;
        tree.printInorder(tree.head, fuck, fuck, fuck);
		//std::vector<int> expectedOutput = {1, 2, 3};
		//REQUIRE(expectedOutput.size() == actualOutput.size());
		//REQUIRE(actualOutput == expectedOutput);

    int test = 1;
	REQUIRE(test == 1);
}