#include "Hash.h"
#include <iostream>

int Hash::size(){
    return counter;
} 

void showlist(list <int> g) 
{ 
    list <int> :: iterator it; 
    for(it = g.begin(); it != g.end(); ++it){ 
        cout << "->" << *it;
    }
    cout << '\n'; 
} 

bool Hash::find(int data){
    int I = data%sizzle;
    list<int> search = htable[I];
    list<int>::iterator it;
    for (it = search.begin(); it != search.end(); ++it){
        if(*it == data){
            return true;
        }
    }
    return false;
} 

bool Hash::insert(int data){
    if(!find(data)){
        int I = data%sizzle;
        htable[I].push_back(data);
        counter++;
        return true;
    }
    return false;
} 

bool Hash::erase(int data){
    if(find(data)){
        int I = data%sizzle;
        htable[I].remove(data);
        counter--;
        return true;
    }
    return false;
}

void Hash::Print(){
    for(int i=0; i < sizzle; ++i){
        cout << "[" << i << "]: ";
        showlist(htable[i]);
    }
}
