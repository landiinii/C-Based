# Lab8-AVL

## Purpose
This lab assignment focuses on self-balancing binary search trees.

## Background
In computer science, an AVL tree is a self-balancing binary search tree, and it was the first such data structure to be invented. In an AVL tree, the heights of the two subtrees of any node differ by at most one. Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases, where n is the number of nodes in the tree prior to the operation. Insertions and deletions may require the tree to be rebalanced by one or more tree rotations.

## Requirements
You will need the files in this git repository to complete this assignment.

### Part 1 - Adding to the Tree  (20 Pts)
* Implement the interface creating an AVL tree. Remember to rebalance when the subtree heights are off by more than 1 (i.e. the balance of a node is greater than 1 or less than -1).

### Part 2 - Remove from the tree  (30 Pts)
* Properly remove from the AVL tree
* Maintain balance of the tree
* Be sure to follow the conventions outlined in the Requirement Notes to keep a "properly" constructed tree

### Part 3 - Add 1 - 20, then Remove the Root until Empty  (10 Pts)
* Adds all integers 1 - 20 to the tree then calls remove on the root node until the tree is empty.  This will require your tree to perform several rebalances.

### Part 4 - Border Cases  (10 Pts)
* Like Part 4 of Lab 6, this will test out several border cases in your AVL tree.

### Part 5 - Add -50 - 50, then Remove -50 - 50  (20 Pts)
* This will thoroughly test your tree by adding all integers -50 - 50, then removing all integers -50 - 50.

### Part 6 - Valgrind  (10 Pts Pass/Fail)
* Run and pass Valgrind on your program to ensure that you have no memory leaks.
* No UML diagram is required for this lab.

## Requirement Notes
* There are multiple correct methods for rebalancing nodes in an AVL tree; each method may result in a unique tree. Some conventions will need to be used to ensure that your tree properly matches ours. When rebalancing, refer to [this simulation](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) for more detailed information on proper balancing.
* You should remove nodes from the AVL tree in the same manner used for the BST.
* Remember to disallow duplicate entries and handle the case when the element to be removed is not in the tree
* You are required to write a separate '.h' and '.cpp' for every class you implement.
* This lab is much easier to implement if you follow the algorithms presented in the course text on pages 634-642.
