#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include "relation.h"

class database: public map<string, relation>
{
    
    private:
    map<string, relation> relations;
    
    public:
    database(){
        
    }
    
    void addTupleToRelation(string name, Tuple *tup);
    void addRelation(string name, relation *relat);
    void toStringer();
    relation getRelation(string name);
    int getRelationSize(string name);
    scheme getScheme(string name);
    
    
};
#endif