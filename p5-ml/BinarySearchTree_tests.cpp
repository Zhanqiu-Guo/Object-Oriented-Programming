// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
using namespace std;

TEST(empty_size_height) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
    
    tree.insert(5);
    ASSERT_TRUE(tree.size() == 1);
    ASSERT_TRUE(tree.height() == 1);
    
    tree.insert(7);
    tree.insert(3);
    ASSERT_TRUE(tree.size() == 3);
    ASSERT_TRUE(tree.height() == 2);
    
    tree.insert(8);
    ASSERT_TRUE(tree.size() == 4);
    ASSERT_TRUE(tree.height() == 3);
    
    tree.insert(9);
    ASSERT_TRUE(tree.size() == 5);
    ASSERT_TRUE(tree.height() == 4);
    
    tree.insert(1);
    ASSERT_TRUE(tree.size() == 6);
    ASSERT_TRUE(tree.height() == 4);
}

TEST(copy_destory){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(4);
    tree.insert(2);
    
    BinarySearchTree<int> tree1(tree);
    ASSERT_TRUE(tree1.size() == 6);
    ASSERT_TRUE(tree1.height() == 3);
    
    //destory
    BinarySearchTree<int> tree2;
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(3);
    tree2.insert(8);
    tree2.insert(100);
    tree2.insert(71);
    tree2.insert(-1);
    tree2.insert(9);
    tree2= tree1;
    ASSERT_TRUE(tree2.size() == 6);
    ASSERT_TRUE(tree2.height() == 3);
    
    BinarySearchTree<int> tree3(tree2);
    BinarySearchTree<int> tree4;
    tree3 = tree4;
    ASSERT_TRUE(tree3.size() == 0);
    ASSERT_TRUE(tree3.height() == 0);
    
    BinarySearchTree<int> tree5;
    BinarySearchTree<int> tree6(tree5);
    ASSERT_TRUE(tree6.size() == 0);
    ASSERT_TRUE(tree6.height() == 0);
    
}

TEST(find){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(6);
    
    ASSERT_TRUE(tree.find(0) == tree.end());
    ASSERT_TRUE(tree.find(8) == ++tree.find(7));
    ASSERT_TRUE(tree.find(3) == tree.min_element());
    ASSERT_TRUE(tree.find(3) == tree.begin());
    ASSERT_TRUE(*(tree.find(5)) == 5);
    ASSERT_TRUE(*(tree.find(6)) == 6);
}

TEST(min_max){
    BinarySearchTree<int> tree2;
    ASSERT_TRUE(tree2.min_element() == tree2.end());
    ASSERT_TRUE(tree2.max_element() == tree2.end());
    tree2.insert(5);
    ASSERT_TRUE(*(tree2.min_element()) == 5);
    ASSERT_TRUE(*(tree2.max_element()) == 5);
    tree2.insert(7);
    tree2.insert(4);
    tree2.insert(2);
    tree2.insert(3);
    tree2.insert(1);
    tree2.insert(8);
    tree2.insert(100);
    tree2.insert(71);
    tree2.insert(-1);
    tree2.insert(9);
    ASSERT_TRUE(*(tree2.min_element()) == -1);
    ASSERT_TRUE(*(tree2.max_element()) == 100);
}

TEST(check_sorting_invariant){
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    *tree.begin() = 8;
    ASSERT_FALSE(tree.check_sorting_invariant());
    
    BinarySearchTree<int> tree1;
    tree1.insert(5);
    tree1.insert(7);
    tree1.insert(3);
    *(++++tree1.begin()) = 0;
    ASSERT_FALSE(tree1.check_sorting_invariant());
    
    BinarySearchTree<int> tree2;
    tree2.insert(5);
    tree2.insert(7);
    tree2.insert(3);
    tree2.insert(8);
    tree2.insert(100);
    tree2.insert(71);
    tree2.insert(-1);
    tree2.insert(9);
    ASSERT_TRUE(tree2.check_sorting_invariant());
    *tree2.begin() = 10;
    ASSERT_FALSE(tree2.check_sorting_invariant());
}

TEST(traverse){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(100);
    tree.insert(71);
    tree.insert(-1);
    tree.insert(9);
    
    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    ASSERT_TRUE(oss_preorder.str() == "5 3 -1 7 8 100 71 9 ");

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    ASSERT_TRUE(oss_inorder.str() == "-1 3 5 7 8 9 71 100 ");
    
    BinarySearchTree<int> tree1;
    ostringstream preorder;
    tree1.traverse_preorder(preorder);
    ASSERT_TRUE(preorder.str() == "");

    ostringstream inorder;
    tree1.traverse_inorder(inorder);
    ASSERT_TRUE(inorder.str() == "");
}

TEST(min_greater_than){
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.min_greater_than(-1) == tree.end());
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(8);
    tree.insert(100);
    tree.insert(71);
    tree.insert(-1);
    tree.insert(9);
    
    ASSERT_TRUE(*(tree.min_greater_than(-1)) == 3);
    ASSERT_TRUE(*(tree.min_greater_than(0)) == 3);
    ASSERT_TRUE(*(tree.min_greater_than(8)) == 9);
    ASSERT_TRUE(*(tree.min_greater_than(12)) == 71);
    ASSERT_TRUE(*(tree.min_greater_than(72)) == 100);
    
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    tree1.insert(13);
    ASSERT_TRUE(*(tree1.min_greater_than(11)) == 13);
    tree1.insert(12);
    tree1.insert(14);
    ASSERT_TRUE(*(tree1.min_greater_than(11)) == 12);
}

TEST_MAIN()
