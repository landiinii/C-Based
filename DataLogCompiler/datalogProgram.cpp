#include "datalogProgram.h"

void datalogProgram::setDomain(){
    for (unsigned i = 0; i<facts.size(); ++i){
        vector<parameter> stuff = facts.at(i).getParams();
        for(unsigned i=0; i<stuff.size(); ++i){
            domain.insert(stuff.at(i).toString());
        }
    }
}

void datalogProgram::toString(){
    cout << "Schemes(" << schemes.size() << "):" << endl;
    for(unsigned i=0; i<schemes.size(); ++i){
        cout << "  " << schemes.at(i).toString() << endl;
    }
    cout << "Facts(" << facts.size() << "):" << endl;
    for(unsigned i=0; i<facts.size(); ++i){
        cout << "  " << facts.at(i).toString() << "." << endl;
    }
    cout << "Rules(" << rules.size() << "):" << endl;
    for(unsigned i=0; i<rules.size(); ++i){
        cout << "  " << rules.at(i).toString() << endl;
    }
    cout << "Queries(" << queries.size() << "):" << endl;
    for(unsigned i=0; i<queries.size(); ++i){
        cout << "  " << queries.at(i).toString() << "?" << endl;
    }
    cout << "Domain(" << domain.size() << "):";
    set<string>::const_iterator i = domain.begin();
    for(i = domain.begin(); i!= domain.end(); ++i){
        cout << endl << "  " << *i;
    }
}

vector<rule> datalogProgram::getRules(){
    return rules;
}

vector<predicate> datalogProgram::returnVector(string type){
    if (type == "scheme"){
        return schemes;
    }
    if (type == "fact"){
        return facts;
    }
    else{
        return queries;
    }
}