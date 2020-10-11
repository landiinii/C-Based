#include "Node.h"

Node::Node(int data){
    this->data = data;
    this->left = NULL;
    this->right = NULL;
}
Node::~Node() {}

int Node::getData() const{
    return data;
}
NodeInterface* Node::getLeftChild() const{
    return left;
}
NodeInterface* Node::getRightChild() const{
    return right;
}