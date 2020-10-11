#include "Node.h"

Node::Node(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 0;
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
int Node::getHeight(){
    return height;
}