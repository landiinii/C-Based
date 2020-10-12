#include "parameter.h"

string parameter::toString(){
    if(type == tokenType::STRING || type == tokenType:: ID){
        return thingy;
    }
    else{
        stringstream final;
        final << "(" << params.at(0) << params.at(1) << params.at(2) << ")";
        return final.str();
    }
}
string parameter::getThing(){
    return thingy;
}
bool parameter::isConstant(){
    return isconstant;
}