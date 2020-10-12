#ifndef PARAMETER_H
#define PARAMETER_H
#include "token.h"

class parameter{
    
protected:
tokenType type;
string thingy = "";
vector<string> params;
bool isconstant;
public:
    parameter(tokenType t, string thing, vector<string> pars){
        type = t;
        if (t == tokenType::STRING || t == tokenType::ID){
            thingy = thing;
            if (t == tokenType::STRING){
                isconstant = true;
            }
            else{
                isconstant = false;
            }
        }
        else{
            params = pars;
        }
    }
    ~parameter(){}
    
    string toString();
    string getThing();
    bool isConstant();
    
};
#endif