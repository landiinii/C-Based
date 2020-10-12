#include "rule.h"
string rule::toString(){
    stringstream rull;
    predicate head(headName, headStuff);
    rull << head.toString() << " :- ";
    for (unsigned i=0; i<body.size()-1; ++i){
        rull << body.at(i).toString() << ",";
    }
    rull << body.back().toString() << ".";
    return rull.str();
}

string rule::getHeadName(){
    return headName;
}
    
vector<parameter> rule::getHead(){
    return headStuff;
}
    
vector<predicate> rule::getBody(){
    return body;
}