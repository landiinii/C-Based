#ifndef AVL_H
#define AVL_H

#include "AVLInterface.h"
#include "Node.h"
#include <iostream>
#include <algorithm>

using namespace std;

class AVL: public AVLInterface
{
private:
public:
	AVL() {}
	~AVL() {clear();}

	
	Node* findSpot(Node*& finder, int data);
	Node* findRemove(Node*& tree, int data);
	bool findPrev(Node* finder, int data);
	Node* findIOP(Node* papa);
	
	
	int isBalanced(Node* tree);
	void updateHeight(Node*& tree);
	int getHeight(Node* tree);
	void balanceNode(Node*& tree);
	void RightRotate(Node*& tree);
	void LeftRotate(Node*& tree);
	
	
	NodeInterface * getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();
	
	
};
#endif