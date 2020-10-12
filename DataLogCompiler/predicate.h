#ifndef PREDICATE_H
#define PREDICATE_H
#include "parameter.h"

class predicate{
    
protected:
string name;
vector<parameter> parameters;
public:
    predicate(string id, vector<parameter> paras){
        name = id;
        parameters = paras;
    }
    ~predicate(){}
    
    string toString();
    string getName();
    vector<parameter> getParams();
    
};
#endif