#include "BST.h"

using namespace std;
Node* root;

NodeInterface * BST::getRootNode() const{
    return root;
}

Node* BST::findPrev(Node* finder, Node* subject){
    cout << "findP  " << finder->data << endl;
    if(finder == NULL){
        return NULL;
    }
    if(finder->data == subject->data){
        return root;
    }
    if(finder->left != NULL){
        if(finder->left->data == subject->data){
            return finder;
        }
    }
    if(finder->right != NULL){
        if(finder->right->data == subject->data){
            return finder;
        }
    }
    if(subject->data < finder->data){
        cout << "ER L" << endl;
        if(finder->left == NULL){
            return NULL;
        }
        return findPrev(finder->left, subject);
    }
    else if(subject->data > finder->data){
        cout << "ER R" << endl;
        if(finder->right == NULL){
            return NULL;
        }
        return findPrev(finder->right, subject);
    }
}

Node* BST::findSpot(Node* finder, int data){
    if(data == finder->data){
        cout << "findA" << endl;
        return NULL;   
    }
    else if(data < finder->data){
        //cout << "find 2.1" << endl;
        if(finder->left == NULL){
            //cout << "find 2.2" << endl;
            return finder;
        }
        else{
            //cout << "find 2.3" << endl;
            return findSpot(finder->left, data);
        }
    }
    else if(data > finder->data){
        //cout << "find 3.1" << endl;
        if(finder->right == NULL){
            //cout << "find 3.2" << endl;
            return finder;
        }
        else{
            //cout << "find 3.3" << endl;
            return findSpot(finder->right, data);
        }
    }
}

bool BST::totalRemove(Node*& subject, Node*& parent){
    cout << "totalRemove ";
    if(parent == subject){
        if(subject->left == NULL){
            root = subject->right;
        }
        if(subject->right == NULL){
            root = subject->left;
        }
        cout << subject->data << " er 1" << endl;
        delete subject;
        return true;
    }
    if(parent->left == subject){
        if(subject->left == NULL){
            parent->left = subject->right;
        }
        if(subject->right == NULL){
            parent->left = subject->left;
        }
        cout << subject->data << " er 2" << endl;
        delete subject;
        return true;
    }
    else{
        if(subject->left == NULL){
            parent->right = subject->right;
        }
        if(subject->right == NULL){
            parent->right = subject->left;
        }
        cout << subject->data << " er 3" << endl;
        delete subject;
        return true;
    }
}

Node* BST::findIOP(Node* papa){
    cout << "findIOP" << endl;
    if(papa != NULL){
        if(papa->right == NULL){
            cout << "null" << endl;
            return papa;
        }
        else{
            cout << "other" << endl;
            return findIOP(papa->right);
        }
    }
    else{
        return NULL;
    }
}

bool BST::dethrone(Node*& dethroned, Node*& parent){
    cout << "dethrone " << dethroned->data << endl;
    Node* heir = NULL;
    heir = findIOP(dethroned->left);
    cout << heir->data << endl;
    Node* temp = heir->left;
    Node* fill = findPrev(root, heir);
    if(fill != dethroned){
        fill->right = temp;
        heir->left = dethroned->left;
    }
    heir->right = dethroned->right;
    if(dethroned == root){
        root = heir;
    }
    else{
        if(parent->right == dethroned) parent->right = heir;
        else if(parent->left == dethroned) parent->left = heir;
    }
    delete dethroned;
    return true;
}

bool BST::add(int data){
    cout << "add " << data << endl;
    if (root == NULL){
        Node* newRoot = new Node(data);
        root = newRoot;
        return true;
    }
    else{
        Node* finder = root;
        finder = findSpot(finder, data);
        if(finder == NULL){
            return false;
        }
        else{
            Node* newNode = new Node(data);
            if(finder->data > data){
                finder->left = newNode;
                return true;
            }
            else{
                finder->right = newNode;
                return true;
            }
        }
    }
}

Node* BST::findRemove(Node* root, int data){
    if(data == root->data){
        return root;   
    }
    else if(data < root->data){
        if(root->left == NULL){
            return NULL;
        }
        else{
            return findRemove(root->left, data);
        }
    }
    else if(data > root->data){
        if(root->right == NULL){
            return NULL;
        }
        else{
            return findRemove(root->right, data);
        }
    }
}

bool BST::remove(int data){
    cout << "remove " << data << endl;
    Node* subject = findRemove(root, data);
    if(subject == NULL){
        return false;
    }
    Node* parent = findPrev(root, subject);
    if(subject->left == NULL && subject->right == NULL){
        if(subject == root){
            delete root;
            root = NULL;
            return true;
        }
        else if(parent->right == subject){
            delete subject;
            parent->right = NULL;
            return true;
        }
        else{
            delete subject;
            parent->left = NULL;
            return true;
        }
        cout << " true " << endl;
    }
    else if(subject->left == NULL || subject->right == NULL){
        if(totalRemove(subject, parent)){
            cout << " True " << endl;
            return true;
        }
        else{
            cout << " False " << endl;
            return false;
        }
    }
    else if(subject->right != NULL && subject->left != NULL){
        return dethrone(subject, parent);
    }
    else{
        return false;
    }
}


void BST::clear(){
    cout << "clear" << endl;
    while(root != NULL){
        remove(root->data);
    }
}
