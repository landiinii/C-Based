#include "Noder.h"

void Noder::addEdge(int nextID){
    children.insert(nextID);
}

void Noder::setVisit(){
    visited = true;
}
    
int Noder::getID(){
    return ID;
}

bool Noder::getVisit(){
    return visited;
}

int Noder::getRevNum(){
    return revNum;
}

void Noder::setRevNum(int newRevNum){
    revNum = newRevNum;
}

string Noder::toString(){
    stringstream ss;
    for (set<int>::iterator it = children.begin(); it != children.end(); ++it){
		ss << "R" << *it << ",";
	}
	string result = ss.str();
	if (result.size() > 0)
	{
		result.erase(result.end() - 1);	//Remove last space
	}
	return result;
}