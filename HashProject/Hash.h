#ifndef HASH_H
#define HASH_H
#include <list>
#include <iterator>
using namespace std;

class Hash{
    
    
private:
    list<int> *htable;
    int sizzle = 0;
    int counter = 0;
public:
    Hash(int tableSize){
        htable = new list<int>[tableSize];
        sizzle = tableSize;
    }
    ~Hash(){
        delete [] htable;
    }
    
    
    // returns the number of items in the set
    int size(); 
    
    // returns true if the integer "data" is in the set and false otherwise
    bool find(int data); 
    
    // inserts the integer "data" into the set if that integer is not already in the set
    // if the integer "data" is already in the set, the integer should not be inserted
    // return true if the function adds the integer to the set, and false otherwise
    bool insert(int data); 
    
    // erases the integer "data" from the set if it is in the set
    // return true if the function removes the integer from the set, and false otherwise
    bool erase(int data);
    void Print();


};
#endif