#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "predicate.h"
#include "rule.h"
#include <set>

class datalogProgram{
    
protected:
vector<predicate> schemes;
vector<predicate> facts;
vector<predicate> queries;
vector<rule> rules;
set<string> domain;
public:
    datalogProgram(vector<predicate> scheme, vector<predicate> fact, vector<predicate> query, vector<rule> ruler){
        schemes=scheme;
        facts=fact;
        queries=query;
        rules=ruler;
        setDomain();
    }
    ~datalogProgram(){}
    
    void setDomain();
    
    void toString();
    
    vector<predicate> returnVector(string type);
    
    vector<rule> getRules();
    
};
#endif