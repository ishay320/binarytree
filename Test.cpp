#include "doctest.h"
#include "sources/BinaryTree.hpp"
#include <iostream>

TEST_CASE("throws")
{
    ariel::BinaryTree<int> tree;

    CHECK_THROWS(tree.add_left(1, 2));
    CHECK_THROWS(tree.add_right(1, 2));
    tree.add_root(3);
    CHECK_THROWS(tree.add_left(1, 2));
    CHECK_THROWS(tree.add_right(1, 2));
}

TEST_CASE("inserts")
{
    ariel::BinaryTree<int> tree;
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(4, 6));
}
TEST_CASE("inorder_iterator")
{
    ariel::BinaryTree<int> tree;
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(4, 6));
    /**
          1
        /   \
       2      3
      / \
    4    5
   /
  6
  inorder: 642513
     */
    int a[6] = {6, 4, 2, 5, 1, 3};
    int *b = a;
    for (auto i : tree)
    {
        CHECK(i == *b);
        b++;
    }
    b = a;
    for (ariel::BinaryTree<int>::inorder_iterator i = tree.begin_inorder(); i != tree.end_inorder(); i++)
    {
        CHECK(i.operator*() == *b);
        b++;
    }
}
TEST_CASE("preorder_iterator")
{
    ariel::BinaryTree<int> tree;
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(4, 6));
    /**
          1
        /   \
       2      3
      / \
    4    5
   /
  6
  preorder: 124653
     */
    int a[6] = {1,2,4,6,5,3};
    int *b = a;
    for (ariel::BinaryTree<int>::preorder_iterator i = tree.begin_preorder(); i != tree.end_preorder(); i++)
    {
        CHECK(i.operator*() == *b);
        b++;
    }
}
TEST_CASE("postorder_iterator")
{
    ariel::BinaryTree<int> tree;
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_left(1, 2));
    CHECK_NOTHROW(tree.add_right(1, 3));
    CHECK_NOTHROW(tree.add_left(2, 4));
    CHECK_NOTHROW(tree.add_right(2, 5));
    CHECK_NOTHROW(tree.add_left(4, 6));
    /**
          1
        /   \
       2      3
      / \
    4    5
   /
  6
  postorder: 645231
     */
    int a[6] = {6,4,5,2,3,1};
    int *b = a;
    for (ariel::BinaryTree<int>::postorder_iterator i = tree.begin_postorder(); i != tree.end_postorder(); i++)
    {
        CHECK(i.operator*() == *b);
        b++;
    }
}