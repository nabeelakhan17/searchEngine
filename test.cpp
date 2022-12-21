#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp" 
#include "AVLTree.h"
#include <fstream>

using namespace std;

TEST_CASE("Check that AVLTree works", "[AVLTree]")
{
    AvlTree<int> avl;
    SECTION("Testing empty")
    {
        REQUIRE(avl.isEmpty());
    }
    SECTION("Testing contains")
    {
        avl.insert(9);
        REQUIRE(avl.contains(9) == true);
    }
    SECTION ("Testing insert")
    {
        avl.insert(1);
        avl.insert(2);
        REQUIRE(avl.isEmpty()==false);
        avl.insert(3);
        avl.insert(4);
        REQUIRE(avl.contains(4));
        avl.insert(5);
        REQUIRE(avl.contains(5));
        avl.prettyPrintTree();

        ofstream outFile("test.txt");
        if (!outFile)
            cout << "oops" << endl;
        else  
            avl.printTreeByLevel(outFile);

    }
    SECTION ("Testing remove")
    {
        avl.remove(3);
        avl.remove(4);
        avl.printTreeByLevel();
        REQUIRE(avl.contains(3)==false);
        REQUIRE(avl.contains(4)==false);


    }
    SECTION("Testing find min")
    {
        AvlTree<int> avl1;
        avl1.insert(1);
        avl1.insert(2);
        REQUIRE(avl1.findMin() == 1);
        avl.prettyPrintTree();

        
    }

    SECTION("Testing find max")
    {
        AvlTree<int> avl1;
        avl1.insert(1);
        avl1.insert(2);
        avl1.insert(9);
        REQUIRE(avl1.findMax() == 9);
    }

}

// testing