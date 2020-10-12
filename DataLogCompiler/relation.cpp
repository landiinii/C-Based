#include "relation.h"
void relation::project(vector<unsigned> *columns){
    

    scheme newschema;
    for(unsigned i = 0; i < columns->size(); ++i){
        newschema.push_back(schemer.at(columns->at(i)));
    }
    schemer = newschema;
    set<Tuple> newtuple;

    
    for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
        Tuple t = *it;
        Tuple newtups;
        
        for(unsigned i = 0; i < columns->size(); ++i){
            newtups.push_back(t.at(columns->at(i)));
        }
        newtuple.insert(newtups);
    }
    tuples = newtuple;
}

void relation::renamer(vector<string> *names){
    for(unsigned i=0; i<schemer.size(); ++i){
        schemer.at(i) = names->at(i);
    }
}

void relation::select1(string constant, int column){
    set<Tuple> newtuple;
    for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
        Tuple t = *it;
        if(t.at(column) == constant){
            newtuple.insert(t);
        }
    }
    tuples = newtuple;
}

void relation::select2(int a, int b){
    for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
        Tuple t = *it;
        if(t.at(a) != t.at(b)){
            tuples.erase(it);
        }
    }
}














//Join Functions

scheme relation::joinSchemes(scheme *second, vector<vector<int> > *sames){
    vector<int> first;
    vector<int> notfirst;
    int h = schemer.size();
    scheme newScheme = schemer;
    for(unsigned i=0; i<second->size(); ++i){
        bool checkflag = false;
        for(int j=0; j<h; ++j){
            if(!checkflag && schemer.at(j) == second->at(i)){
                first.push_back(j);
                notfirst.push_back(i);
                checkflag=true;
            }
        }
        if(!checkflag){
            newScheme.push_back(second->at(i));
        }
    }
    sames->push_back(first);
    sames->push_back(notfirst);
    return newScheme;
}

bool isJoinable(Tuple *a, Tuple *b, vector<vector<int> > *sames){
    bool checker = true;
    for(unsigned i=0; i<sames->at(0).size(); ++i){
        if (a->at(sames->at(0).at(i)) != b->at(sames->at(1).at(i))){
            checker = false;
        }
    }
    return checker;
}

relation relation::joinTuples(vector<vector<int> > *sames, set<Tuple> *other, scheme *newScheme){
    relation newRelation("result", *newScheme);
    if(!sames->empty()){
        //cout << "some same" << endl;
        for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
            for(set<Tuple>::iterator it2=other->begin(); it2!=other->end(); ++it2){
                Tuple a = *it;
                Tuple b = *it2;
                if(isJoinable(&a, &b, sames)){
                    //cout << "yes" << endl;
                    set<int> v1;
                    for(unsigned i=0; i<sames->at(1).size(); ++i){
                        v1.insert(sames->at(1).at(i));
                    }
                    for(set<int>::reverse_iterator rit = v1.rbegin(); rit != v1.rend(); ++rit){
                        int taker = *rit;
                        b.erase(b.begin()+taker);
                    }
                    for(unsigned i=0; i<b.size(); ++i){ 
                        a.push_back(b.at(i));
                    }
                    if(a.size() == newScheme->size()){
                        //cout << "--gotem" << endl;
                        newRelation.addTuple(&a);
                    }
                    //else{cout << "--nope" << endl;}
                }
                //else {cout << "no" << endl;}
            }
        }
    }
    else if(!other->empty()){
        //cout << "none same" << endl;
        for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
            Tuple a = *it;
            for(set<Tuple>::iterator it2=other->begin(); it2!=other->end(); ++it2){
                Tuple b = *it2;
                for(unsigned i=0; i<b.size(); ++i){
                    a.push_back(b.at(i));
                }
            }
            newRelation.addTuple(&a);
        }
    }
    return newRelation;
}

relation relation::join(relation *joiner){
    scheme second = joiner->getScheme();
    set<Tuple> other = joiner->getTuples();
    vector<vector<int> > sames;
    
    scheme newScheme; 
    if(!other.empty()){
        newScheme = joinSchemes(&second, &sames);
    }
    
    return joinTuples(&sames, &other, &newScheme);
}











//Other Functions

void relation::addTuple(Tuple *tupler){
    tuples.insert(*tupler);
}

scheme relation::getScheme(){
    return schemer;
}

set<Tuple> relation::getTuples(){
    return tuples;
}

string relation::getName(){
    return name;
}

void relation::setName(string newName){
    name = newName;
}

void relation::toString(){
    //cout << name << " " << tuples.size() << endl;
    for(set<Tuple>::iterator it=tuples.begin(); it!=tuples.end(); ++it){
        Tuple tupp = *it;
        cout << endl << "  ";
        //cout << tupp.size() << "=" << schemer.size() << endl;
        for(unsigned i=0; i<tupp.size()-1; ++i){
            cout << schemer.at(i) << "=" << tupp.at(i) << ", ";
        }
        cout << schemer.at(tupp.size()-1) << "=" << tupp.at(tupp.size()-1);
    }
}

int relation::getSize(){
    if (tuples.empty()){
        return 0;
    }
    else{
        return tuples.size();
    }
}

void relation::setScheme(scheme *newScheme){
    schemer = *newScheme;
}