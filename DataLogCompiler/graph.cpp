#include "graph.h"

void graph::addNode(int ID, Noder newNode){
    nodes[ID] = newNode;
}

void graph::addEdge(int from, int to){
    nodes[from].addEdge(to);
}

void graph::setRevNum(int ID, int revNum){
    nodes[ID].setRevNum(revNum);
}

stack<int> graph::revDFS(){
    for(map<int, Noder>::iterator it = nodes.begin(); it != nodes.end(); ++it){
		if (!it->second.getVisit())
		{
			revDFS(it->second);
		}
	}
	return revRevNum;
}

void graph::revDFS(Noder& currentNode){
    currentNode.setVisit();
	for (set<int>::iterator it = currentNode.children.begin(); it != currentNode.children.end(); it++){
		if (!nodes[*it].getVisit())
		{
			revDFS(nodes[*it]);
		}
	}
	currentNode.setRevNum(revCount);
	revRevNum.push(currentNode.getID());
	revCount++;
}

vector<set<int>> graph::sccDFS(stack<int> idOrder){
    while (!idOrder.empty())
	{
		if (!nodes[idOrder.top()].getVisit())
		{
			SCCs.push_back(set<int>());	
			sccDFS(nodes[idOrder.top()]);
			sccCount++;
		}
		idOrder.pop();
	}
	return SCCs;
}

void graph::sccDFS(Noder& currentNode){
    currentNode.setVisit();
	for (set<int>::iterator it = currentNode.children.begin(); it != currentNode.children.end(); ++it)
	{
		if (!nodes[*it].getVisit())
		{
			sccDFS(nodes[*it]);
		}
	}
	SCCs[sccCount].insert(currentNode.getID());
}



void graph::printGraph(){
    for(map<int, Noder>::iterator it = nodes.begin(); it != nodes.end(); ++it){
        cout << "R" << it->first << ":";
        cout << it->second.toString() << endl;
    }
}
