#ifndef BST_H
#define BST_H

#include "BSTInterface.h"
#include "Node.h"
#include <iostream>

using namespace std;

class BST: public BSTInterface
{
private:
public:
	BST() {}
	~BST() {clear();}

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;
	Node* findSpot(Node* finder, int data);
	bool totalRemove(Node*& subject, Node*& parent);
	Node* findRemove(Node* root, int data);
	bool dethrone(Node*& dethroned, Node*& parent);
	Node* findPrev(Node* finder, Node* subject);
	Node* findIOP(Node* papa);
	/*
	* Attempts to add the given int to the BST tree
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the BST tree
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
};
#endif