#ifndef PARSER_H
#define PARSER_H
#include "scanner.h"
#include "datalogProgram.h"

using namespace std;

class parser{
    
protected:
vector<token> tokens;
int position;
public:
    parser(string filename){
        scanner File(filename);
        for(int i=0; i<File.getTokenSize(); ++i){
            token pass = File.getToken(i);
            if(pass.getType() == tokenType::UNDEFINED){
                throw pass;
            }
            else{
                tokens.push_back(pass);
            }
        }
        position = 0;
    }
    ~parser(){
        
    }
    
    datalogProgram parseIt();
    void printIt(datalogProgram data);
    
    datalogProgram parseDatalogProgram();
    void parseSchemeList(vector<predicate> *schemes);
    void parseFactList(vector<predicate> *facts);
    void parseRuleList(vector<rule> *rules);
    void parseQueryList(vector<predicate> *queries);
    predicate parseScheme();
    predicate parseFact();
    rule parseRule();
    predicate parseQuery();
    predicate parseHeadPredicate();
    predicate parsePredicate();
    void parsePredicateList(vector<predicate> *body);
    void parseParameterList(vector<parameter> *params);
    void parseStringList(vector<parameter> *params);
    void parseIdList(vector<parameter> *params);
    parameter parseParameter();
    vector<string> parseExpression();
    string parseOperator();
    
    
    
};

#endif