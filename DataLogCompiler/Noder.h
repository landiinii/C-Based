#ifndef NODER_H
#define NODER_H
#include "relation.h"
#include<sstream>
class Noder
{
    friend class graph;
    private:
        bool visited = false;
        set<int> children;
        int ID;
        int revNum =0;        
    public:
    
    Noder(){}
    Noder(int id){ID = id;}
    
    void addEdge(int nextID);
    
    void setVisit();
    
    int getID();
    
    bool getVisit();

    int getRevNum();

    void setRevNum(int newRevNum);
    
    string toString();
   
};
#endif