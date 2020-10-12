#ifndef RELATION_H
#define RELATION_H
#include "Tuple.h"
#include "scheme.h"
#include <set>
#include <string>


class relation{
    
    private:
    set<Tuple> tuples;
    string name;
    scheme schemer;
    
    
    public:
    
    relation(string nombre, scheme eschemer){
        name = nombre;
        schemer = eschemer;
    }
    
    void addTuple(Tuple *tupler);
    void toString();
    string getName();
    void setName(string newName);
    int getSize();
    scheme getScheme();
    void setScheme(scheme *newScheme);
    set<Tuple> getTuples();
    
    
    
    void project(vector<unsigned> *columns);
    void renamer(vector<string> *names);
    void select1(string constant, int column);
    void select2(int a, int b);
    
    
    
    
    relation join(relation *joiner);
    relation joinTuples(vector<vector<int> > *sames, set<Tuple> *other, scheme *newScheme);
    scheme joinSchemes(scheme *second, vector<vector<int> > *sames);

    
};
#endif