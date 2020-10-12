#ifndef RULE_H
#define RULE_H
#include "predicate.h"

class rule{
    
protected:
string headName;
vector<parameter> headStuff;
vector<predicate> body;
public:
    rule(){}

    rule(predicate header, vector<predicate> bodyer){
        headName = header.getName();
        headStuff = header.getParams();
        body=bodyer;
    }
    ~rule(){}
    
    string getHeadName();
    
    vector<parameter> getHead();
    
    vector<predicate> getBody();
    
    string toString();
    
};
#endif