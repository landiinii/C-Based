#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "datalogProgram.h"
#include "database.h"
#include "graph.h"
#include<sstream>
class interpreter
{
    private:
    datalogProgram Data;
    database DB;
    vector<scheme> schemes;
    vector<predicate> queries;
    vector<rule> rules;
    bool emptiness = true;
    
    map<int, bool> selfDependent;
    
    public:
    interpreter(datalogProgram data) : Data(data){
        Data = data;
        queries = data.returnVector("q");
        rules = data.getRules();
        makeRelations();
        makeTuples();
        organizeRules();
        evaluateQueries();
    }
    
    void makeRelations();
    void makeTuples();
    
    void evaluateQueries();
    relation solveQ(predicate *q);
    
    void evaluateRules(vector<rule> *selur);
    void singleRun(rule *mean);
    relation evaluateBody(rule *ruler);
    vector<unsigned> evaluateHead(rule *ruler, scheme *rscheme);
    
    
    void organizeRules();
    vector<set<int> > createSCC();
    
};
#endif