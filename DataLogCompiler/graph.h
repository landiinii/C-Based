#ifndef GRAPH_H
#define GRAPH_H
#include "relation.h"
#include "Noder.h"
#include "rule.h"
#include<map>
#include<stack>
class graph
{
    
    private:
    map<int, Noder> nodes;
    stack<int> revRevNum;
    vector<set<int> > SCCs;
    int revCount = 1;
    int sccCount = 0;
    
    public:
    graph(){}
    void addNode(int ID, Noder newNode);
    void addEdge(int from, int to);
    void setRevNum(int ID, int revNum);
    stack<int> revDFS();
    void revDFS(Noder& currentNode);
    vector<set<int>> sccDFS(stack<int> idOrder);
    void sccDFS(Noder& currentNode);
    
    void printGraph();
};
#endif