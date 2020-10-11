#ifndef LINK_LIST_H
#define LINK_LIST_H
#include "LinkedListInterface.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

template<typename T>
class LinkedList : public LinkedListInterface<T>
{
private:

struct Node{
    Node(T val) {
        value = val;
        next = NULL;
    }
    T value;
    Node *next;
};
Node *head = NULL;
int n = 0;


public:

	LinkedList(){
	    head = NULL;
	};
	~LinkedList(){
	    clear();
	};

	/*
	insertHead

	A node with the given value should be inserted at the beginning of the list.

	Do not allow duplicate values in the list.
	*/
	bool checkDuplicate(T value){
	    Node *finder = head;
	    if(n != 0){
	        if(head->value == value){
	            return true;
	        }
    	    while(finder->next != NULL && finder->next->value != value){
    	        finder = finder->next;
    	    }
    	    if(finder->next == NULL){
    	        return false;
    	    }
    	    else{
    	        return true;
    	    }
	    }
	    return false;
	}
	
	void insertHead(T value){
	    if(checkDuplicate(value)){
	        return;
	    }	        
	    else{
	    	Node *newHead = new Node(value);
	        if(head == NULL){
	            head = newHead;
	            head->next = NULL;
	            n++;
	        }
	        else{
    	        newHead->next = head;
    	        head = newHead;
    	        n++;
	        }
	        return;
	    }
	}

	/*
	insertTail

	A node with the given value should be inserted at the end of the list.

	Do not allow duplicate values in the list.
	*/
	void insertTail(T value){
	    if(checkDuplicate(value)){
	        return;
	    }
        else{
            if(head == NULL){
				insertHead(value);
				return;
	        }
	        else{
	        	Node *newTail = new Node(value);
	            Node *friter = head;
	            while(friter->next != NULL){
	                friter = friter->next;
	            }
	            friter->next = newTail;
	            n++;
	        	return;
	        }
	    }
	}

	/*
	insertAfter

	A node with the given value should be inserted immediately after the
	node whose value is equal to insertionNode.

	A node should only be added if the node whose value is equal to
	insertionNode is in the list. Do not allow duplicate values in the list.
	*/
	void insertAfter(T value, T insertionNode){
	    if(checkDuplicate(value)){
	        return;
	    }
	    else{
	        Node *finder = head;
            while (finder != NULL && finder->value != insertionNode) {
                finder = finder->next;
            }
            if(finder == NULL){
                return;
            }
            else if(finder->value == insertionNode){
                Node *after = new Node(value);
                after->next = finder->next;
                finder->next = after;
                n++;
                return;
            }
	    }
	}

	/*
	remove

	The node with the given value should be removed from the list.

	The list may or may not include a node with the given value.
	*/
	void remove(T value){
	    if(head != NULL){
    	    Node *finder = head;
    	    Node *cut = NULL;
    	    Node *holder = NULL;
    	    if(head->value == value){
	            holder = head;
                head = head->next;
                delete holder;
                --n;
	            return;
    	    }
            while(finder->next != NULL && finder->next->value != value){
        	    finder = finder->next;
            }
        	if(finder->next == NULL){
        	    return;
        	}
        	cut = finder->next;
			finder->next = cut->next;
            delete cut;
            --n;
	    }
	    return;
	}

	/*
	clear

	Remove all nodes from the list.
	*/
	void clear(){
	    while(head != NULL){
	        remove(head->value);
	    }
	    n = 0;
	    return;
	}

	/*
	at

	Returns the value of the node at the given index. The list begins at
	index 0.

	If the given index is out of range of the list, throw an out of range exception.
	*/
	T at(int index){
	    if(index < n && index >= 0){
    	    Node *u = head;
    	    for(int i = 0; i < index; ++i){
    	        u = u->next;
    	    }
    	    return u->value;
	    }
	    else{
	        throw out_of_range (" ");
	    }
	    
	}

	/*
	size

	Returns the number of nodes in the list.
	*/
	int size(){
	    return n;
	}

	/*
	toString
	
	Returns a string representation of the list, with the value of each node listed in order (Starting from the head) and separated by a single space
	There should be no trailing space at the end of the string

	For example, a LinkedList containing the value 1, 2, 3, 4, and 5 should return
	"1 2 3 4 5"
	*/
	string toString(){
	    stringstream ss;
	    Node *iterator = head;
	    while(iterator != NULL){
	        if(iterator->next == NULL){
	            ss << iterator->value;
	        }
	        else{
	            ss << iterator->value << " ";
	        }
	        iterator = iterator->next;
	    }
	    return ss.str();
	}

};
#endif