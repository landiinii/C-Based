#include "AVL.h"

using namespace std;
Node* root;


int AVL::isBalanced(Node* tree){
    if (tree == NULL){
        return 0;
    }
    int diff = getHeight(tree->left) - getHeight(tree->right);
    return diff;
}

void AVL::updateHeight(Node*& tree){
    if (tree == NULL){
        return;
    }
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
}

int AVL::getHeight(Node* tree){
    if (tree == NULL){
        return -1;
    }
    return tree->height;
}

void AVL::RightRotate(Node*& tree){
    Node* tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    updateHeight(tree);
    updateHeight(tmp);
    tree = tmp;
}

void AVL::LeftRotate(Node*& tree){
    Node* temp = tree->right;
    tree->right = temp->left;
    temp->left = tree;
    updateHeight(tree);
    updateHeight(temp);
    tree = temp;
}

void AVL::balanceNode(Node*& tree){
    int bCase = isBalanced(tree);
    int lCase = isBalanced(tree->left);
    int rCase = isBalanced(tree->right);
    
    
    //Left Imbalance
    if (bCase > 1){
        if (lCase < 0){
            LeftRotate(tree->left);
            RightRotate(tree);
        }
        else{
            RightRotate(tree);
        }
    }
    //Right Imbalance
    else if (bCase < -1){
        if (rCase > 0){
            RightRotate(tree->right);
            LeftRotate(tree);
        }
        else{
            LeftRotate(tree);
        }
    }
}


NodeInterface * AVL::getRootNode() const{
    return root;
}

bool AVL::findPrev(Node* finder, int data){
    if(finder == NULL){
        return false;
    }
    if(data < finder->data){
        if(finder->left == NULL){
            return NULL;
        }
        return findPrev(finder->left, data);
    }
    else if(data > finder->data){
        if(finder->right == NULL){
            return NULL;
        }
        return findPrev(finder->right, data);
    }
    else{
        return true;
    }
}

Node* AVL::findSpot(Node*& finder, int data){
    if(data == finder->data){
        return NULL;
    }
    else if(data < finder->data){
        if(finder->left == NULL){
            Node* newNode = new Node(data);
            finder->left = newNode;
            newNode->height = 0;
            updateHeight(finder);
            return newNode;
        }
        else{
            Node* temp = findSpot(finder->left, data);
            int balance = isBalanced(finder);
            if (balance > 1 || balance < -1){
                balanceNode(finder);
            }
            updateHeight(finder);
            return temp;
        }
    }
    else if(data > finder->data){
        if(finder->right == NULL){
            Node* newNode = new Node(data);
            finder->right = newNode;
            newNode->height = 0;
            updateHeight(finder);
            return newNode;
        }
        else{
            Node* temp = findSpot(finder->right, data);
            int balance = isBalanced(finder);
            if (balance > 1 || balance < -1){
                balanceNode(finder);
            }
            updateHeight(finder);
            return temp;
        }
    }
}

Node* AVL::findIOP(Node* papa){
    if(papa != NULL){
        if(papa->right == NULL){
            return papa;
        }
        else{
            return findIOP(papa->right);
        }
    }
    else{
        return NULL;
    }
}

bool AVL::add(int data){
    if (root == NULL){
        Node* newRoot = new Node(data);
        root = newRoot;
        root->height = 0;
        return true;
    }
    else{
        Node* finder = findSpot(root, data);
        if(finder == NULL){
            return false;
        }
        else{
            return true;
        }
    }
}

Node* AVL::findRemove(Node*& tree, int data){
    if(tree == NULL){
        return tree;
    }
    else if(data < tree->data){
        tree->left = findRemove(tree->left, data);
        if(tree->left != NULL){
            updateHeight(tree->left);
            int balance = isBalanced(tree->left);
            if (balance > 1 || balance < -1){
                balanceNode(tree->left);
            }
            updateHeight(tree->left);
        }
    }
    else if(data > tree->data){
        tree->right = findRemove(tree->right, data);
        if(tree->right != NULL){
            updateHeight(tree->right);
            int balance = isBalanced(tree->right);
            if (balance > 1 || balance < -1){
                balanceNode(tree->right);
            }
            updateHeight(tree->right);
        }

        
    }
    else{
        if (tree->left == NULL){
            Node* temp = tree->right; 
            delete tree;
            return temp; 
        } 
        else if (tree->right == NULL){
            Node* temp = tree->left; 
            delete tree; 
            return temp; 
        }
        Node* temp = findIOP(tree->left);
        tree->data = temp->data;
        tree->left = findRemove(tree->left, temp->data);
        if(tree->left != NULL){
            updateHeight(tree->left);
            int balance = isBalanced(tree->left);
            if (balance > 1 || balance < -1){
                balanceNode(tree->left);
            }
            updateHeight(tree->left);
        }
    }
    updateHeight(tree);
    int balance = isBalanced(tree);
    if (balance > 1 || balance < -1){
        balanceNode(tree);
    }
    updateHeight(tree);
    return tree;
}

bool AVL::remove(int data){
    if(root->data == data){
        if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
            return true;
        }
        else if (root->left == NULL){
            root->data = root->right->data;
            delete root->right;
            root->right = NULL;
            return true;
        }
        else if (root->right == NULL){
            root->data = root->left->data;
            delete root->left;
            root->left = NULL;
            return true;
        }
    }
    if(findPrev(root, data)){
        findRemove(root, data);
        return true;
    }
    return false;
    
}


void AVL::clear(){
    while(root != NULL){
        remove(root->data);
    }
}
