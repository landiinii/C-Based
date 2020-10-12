#include "predicate.h"
string predicate::toString(){
    stringstream result;
    result << name << "(";
    for(unsigned i=0; i<parameters.size()-1; ++i){
        result << parameters.at(i).toString() << ",";
    }
    result << parameters.back().toString() << ")";
    return result.str();
}
string predicate::getName(){
    return name;
}
vector<parameter> predicate::getParams(){
    return parameters;
}