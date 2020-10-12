#include "interpreter.h"

void interpreter::makeRelations(){
    vector<predicate> schemes = Data.returnVector("scheme");
    for(unsigned i=0; i<schemes.size(); ++i){
        vector<parameter> attributes = schemes.at(i).getParams();
        scheme schemer;
        for(unsigned j=0; j<attributes.size(); ++j){
            string value = attributes.at(j).getThing();
            schemer.push_back(value);
        }
        relation schemed(schemes.at(i).getName(), schemer);
        DB.addRelation(schemed.getName(), &schemed);
    }
}

void interpreter::makeTuples(){
    vector<predicate> tuples = Data.returnVector("fact");
    for(unsigned i=0; i<tuples.size(); ++i){
        vector<parameter> values = tuples.at(i).getParams();
        Tuple tupler;
        for(unsigned j=0; j<values.size(); ++j){
            string value = values.at(j).getThing();
            tupler.push_back(value);
        }
        DB.addTupleToRelation(tuples.at(i).getName(), &tupler);
    }
}

relation interpreter::evaluateBody(rule *ruler){
    vector<predicate> body = ruler->getBody();
    predicate first = body.at(0);
    relation result = solveQ(&first);
    for(unsigned i=1; i<body.size(); ++i){
        predicate next = body.at(i);
        relation f = solveQ(&next);
        result = result.join(&f);
    }
    return result;
}

vector<unsigned> interpreter::evaluateHead(rule *ruler, scheme *rscheme){
    vector<parameter> head = ruler->getHead();
    vector<unsigned> ret;
    for(unsigned i = 0; i<head.size(); ++i){
        for(unsigned j=0; j<rscheme->size(); ++j){
            if(head.at(i).getThing() == rscheme->at(j)){
                ret.push_back(j);
            }
        }
    }
    return ret;
}

void interpreter::evaluateRules(vector<rule> *selur){
    bool FPA;
    int n=0;
    do{
        FPA = false;
        n++;
        for(unsigned i=0; i<selur->size(); ++i){
            rule mean = selur->at(i);
            string rulest = mean.toString();
            cout << endl << rulest;
            relation result = evaluateBody(&mean);
            result.setName(mean.getHeadName());
            scheme schem = result.getScheme();
            vector<unsigned> columns = evaluateHead(&mean, &schem);
            result.project(&columns);
            string rname = result.getName();
            scheme renames = DB.getScheme(rname);
            result.setScheme(&renames);
            
            
            set<Tuple> t = result.getTuples();
            for(set<Tuple>::iterator it=t.begin(); it!=t.end(); ++it){
                int presize = DB.getRelationSize(rname);
                Tuple tup = *it;
                DB.addTupleToRelation(rname, &tup);
                int endsize = DB.getRelationSize(rname);
                if(endsize != presize){
                    FPA = true;
                    cout << endl << "  ";
                    for(unsigned i=0; i<tup.size()-1; ++i){
                        cout << renames.at(i) << "=" << tup.at(i) << ", ";
                    }
                    cout << renames.at(tup.size()-1) << "=" << tup.at(tup.size()-1); 
                }
            }
            
        }
    }while(FPA);
    cout << endl << n << " passes: ";

}



void interpreter::singleRun(rule *mean){
    string rulest = mean->toString();
    cout << endl << rulest;
    relation result = evaluateBody(mean);
    result.setName(mean->getHeadName());
    scheme schem = result.getScheme();
    vector<unsigned> columns = evaluateHead(mean, &schem);
    result.project(&columns);
    string rname = result.getName();
    scheme renames = DB.getScheme(rname);
    result.setScheme(&renames);
    set<Tuple> t = result.getTuples();
    for(set<Tuple>::iterator it=t.begin(); it!=t.end(); ++it){
        int presize = DB.getRelationSize(rname);
        Tuple tup = *it;
        DB.addTupleToRelation(rname, &tup);
        int endsize = DB.getRelationSize(rname);
        if(endsize != presize){
            cout << endl << "  ";
            for(unsigned i=0; i<tup.size()-1; ++i){
                cout << renames.at(i) << "=" << tup.at(i) << ", ";
            }
            cout << renames.at(tup.size()-1) << "=" << tup.at(tup.size()-1); 
        }
    }
    cout << endl << "1 passes: ";

}



void interpreter::evaluateQueries(){
    cout << "Query Evaluation" << endl;

    for(unsigned i=0; i<queries.size(); ++i){
        predicate quer = queries.at(i);
        string query = quer.toString() + "?";
        if(i==0){
            cout << query << " ";
        }
        else{
            cout << endl << query << " ";
        }
        relation result = solveQ(&quer);
        
        if(result.getSize()==0){
            cout << "No";
        }
        else if (result.getSize() != 0 && !emptiness){
            cout << "Yes(" << result.getSize() << ")";
            emptiness = true;
        }
        else{
            cout << "Yes(" << result.getSize() << ")";
            result.toString();
        }
    }
}

relation interpreter::solveQ(predicate *q){
    map<string, int> variables;
    string nombre = q->getName();
    vector<parameter> params = q->getParams();
    relation r = DB.getRelation(nombre);
    vector<string> names;
    emptiness = true;
    vector<unsigned> columns;
    for(unsigned i=0; i<params.size(); ++i){
        string vid = params.at(i).getThing();
        if(params.at(i).isConstant()){
            r.select1(vid, i);
        }
        else if(variables.empty() || variables.find(vid) == variables.end()){
            
            variables[vid] = i;
            names.push_back(vid);
            columns.push_back(i);
        }
        else{
            r.select2(variables.at(vid), i);
        }
    }
    if(variables.empty() && r.getSize()>0){
        emptiness = false;
        return r;
    }
    
    if(columns.size()>0){
        r.project(&columns);
        r.renamer(&names);
    }
    return r;
}




vector<set<int> > interpreter::createSCC(){
    graph forward;
    graph backward;
    rule currentRule;
    for(unsigned i=0; i<rules.size(); ++i){
        Noder currentNode = Noder(i);
        forward.addNode(i, currentNode);
        backward.addNode(i, currentNode);
        selfDependent[i] = false;
    }
    for(unsigned i=0; i<rules.size(); ++i){
        currentRule = rules.at(i);
        vector<predicate> body = currentRule.getBody();
        for(unsigned j=0; j<body.size(); ++j){
            for(unsigned k=0; k<rules.size(); ++k){
                if(rules.at(k).getHeadName() == body.at(j).getName()){
                    if(i==k){
                        selfDependent[i] = true;
                    }
                    forward.addEdge(i, k);
                    backward.addEdge(k, i);
                }
            }
        }
    }
    cout<<"Dependency Graph" << endl;
    forward.printGraph();
    
    return forward.sccDFS(backward.revDFS());
}



void interpreter::organizeRules(){
    vector<set<int> > sccList = createSCC();
    cout << endl << "Rule Evaluation" << endl;
    for(unsigned i=0; i<sccList.size(); ++i){
        vector<rule> newRules;
        cout << "SCC: ";
        stringstream ss;
        for(set<int>::iterator it = sccList.at(i).begin(); it!=sccList.at(i).end(); ++it){
        	ss << "R" << *it << ",";
        }
        string result = ss.str();
    	if (result.size() > 0)
    	{
    		result.erase(result.end() - 1);	//Remove last space
    	}
        cout << result;
        set<int>::iterator first = sccList.at(i).begin();
        if(sccList.at(i).size() == 1 && !selfDependent[*first]){
            rule mean = rules.at(*first);
            singleRun(&mean);
        }
        else{
            for(set<int>::iterator it = sccList.at(i).begin(); it!=sccList.at(i).end(); ++it){
        	    newRules.push_back(rules.at(*it));
            }
            evaluateRules(&newRules);
        }
        stringstream rr;
        for(set<int>::iterator it = sccList.at(i).begin(); it!=sccList.at(i).end(); ++it){
        	rr << "R" << *it << ",";
        }
        string str = rr.str();
    	if (str.size() > 0)
    	{
    		str.erase(str.end() - 1);
    	}
    	cout << str << endl;
    }    
    cout << endl;
}