#include "database.h"

void database::addTupleToRelation(string name, Tuple *tup){
    relations.at(name).addTuple(tup);
}

void database::addRelation(string name, relation* relat){
    relations.insert({name, *relat});
}

void database::toStringer(){
    for(map<string,relation>::iterator it=relations.begin(); it!=relations.end(); ++it){
        cout << it->first << ": " << endl;
        relation relat = it->second;
        relat.toString();
        cout << endl;
    }
}

relation database::getRelation(string name){
    return relations.at(name);
}

scheme database::getScheme(string name){
    return relations.at(name).getScheme();
}

int database::getRelationSize(string name){
    int ret = relations.at(name).getSize();
    return ret;
}