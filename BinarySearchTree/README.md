# Lab7-BST

## Purpose
To learn how to add and remove from a binary search tree. This lab will prepare you for the upcoming AVL lab.

## WARNING
You will build off of your code in this lab for the next (AVL) lab.  If you want to have a miserable time finishing the AVL lab, use code that you don't understand for this lab.  In other words, don't use any code you don't understand.

## Background
A binary search tree (BST), which may sometimes be called an ordered or sorted binary tree, is a node-based data structure where each node references a value, a left child, and a right child. Binary search trees are characterized by the following properties:

* The left subtree of a node contains only nodes with values less than the node's value.
* The right subtree of a node contains only nodes with values greater than the node's value.
* There must be no duplicate nodes.
* Both the left and right subtrees of a node also must be binary search trees (each subtree must have the first three properties). [Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)

## Requirements
You will need these files to complete this assignment: BST.zip  Download 

### Part 1 - Add Nodes to the Tree (13 points)
* Implement the NodeInterface getRootNode() function and the add() function.
* You must use your implementation of NodeInterface properly in the structure of your binary search tree.

### Part 2 - Remove and Clear (26 points)
* Implement the remove() and clear() methods from the BSTInterface.
* There are several logically correct ways to remove from a binary search tree. See the requirement notes for instructions on how to remove correctly to pass the test driver.

### Part 3 - More intricate adds and removes (13 points)
* This will more thoroughly test your add and remove() functions.

### Part 4 - Border cases and step-by-step removal (13 points)
* Make sure that your tree doesn't accept duplicates, successfully handles invalid remove requests, etc.

### Part 5 - Full step-by-step removal from a tree (13 points)
* Adds all the integers 0-20 to your tree then removes them one at a time until the tree is empty.

### Part 6 - Valgrind  (22 points Pass/Fail)
*Note: This is worth more because it will help you in the AVL lab.*
* Run and pass Valgrind on your program to ensure that you have no memory leaks.
* You must pass parts 1 - 5 as well as Valgrind to receive credit for this part.

### Requirement Notes
* There are multiple correct methods for removing nodes from a tree; each method may result in a distinct tree. Some conventions need to be used to ensure that your tree properly matches ours. When removing a node with only one child, replace that node with its child and use the in-order predecessor when removing nodes with two children).
* Remember to disallow duplicate entries and to handle the case when the element to be removed is not in the tree.
You are required to write a separate '.h' and '.cpp' for every class you implement.
You may not use any standard library data structures for this lab (vector, list, etc.).
There are many correct ways to implement node objects for linked structures. These include but are not limited to: friend classes, internal classes, and non-internal/non-friend class with various getter and setter functions.  Since this lab is most easily completed when passing node pointers by reference, it is essential that we have direct access to the left and right pointers of the node objects.
* Simple getters of the return type `Node*`, create copies and are incompatible with functions which expect `Node*&`. Therefore the functions used by the test driver `getRightChild()` and `getLeftChild()` will not suit our needs. Any of the three strategies listed below will be sufficient.
* Friend Classes: the Node Class will list the BST class as its friend, not the other way around. This allows private data members to be visible to listed friends.
* Inner (Nested) Classes/Structs: almost identical to the convention we used in the LinkedList lab, but include the inheritance statement to the NodeInterface.  If the inner class is declared private, its public data members will not exceed the scope of the containing class. 
* Non-Friend, Non-Inner classes: in this case, you can write extra getter and setter functions (along side the test driver required getters), with the return type of `Node*&`, which will be compatible with functions requiring `Node*&`. This way you can protect your private data members while still using reference parameters.
