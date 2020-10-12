#include "parser.h"

datalogProgram parser::parseIt(){
    datalogProgram data = parseDatalogProgram();
    //printIt(data);
    return data;
}
/*
void parser::printIt(datalogProgram data){
    cout << "Success!" << endl;
    data.toString();
}
*/


datalogProgram parser::parseDatalogProgram(){
    vector<predicate> schemes;
    vector<predicate> facts;
    vector<predicate> queries;
    vector<rule> rules;
        if(tokens.at(position).getType() == tokenType::SCHEMES){
            position++;
        }
        else{
            throw tokens.at(position);
        }
        if(tokens.at(position).getType() == tokenType::COLON){
            position++;
        }
        else {
            throw tokens.at(position);
        }
schemes.push_back(parseScheme());
parseSchemeList(&schemes);
        if(tokens.at(position).getType() == tokenType::FACTS){
            position++;
        }
        else{
            throw tokens.at(position);
        }
        if(tokens.at(position).getType() == tokenType::COLON){
            position++;
        }
        else {
            throw tokens.at(position);
        }
parseFactList(&facts);
        if(tokens.at(position).getType() == tokenType::RULES){
            position++;
        }
        else{
            throw tokens.at(position);
        }
        if(tokens.at(position).getType() == tokenType::COLON){
            position++;
        }
        else {
            throw tokens.at(position);
        }
parseRuleList(&rules);
        if(tokens.at(position).getType() == tokenType::QUERIES){
        position++;
        }
        else{
            throw tokens.at(position);
        }
        if(tokens.at(position).getType() == tokenType::COLON){
            position++;
        }
        else {
            throw tokens.at(position);
        }
queries.push_back(parseQuery());
parseQueryList(&queries);

datalogProgram program(schemes, facts, queries, rules);
return program;
}

void parser::parseSchemeList(vector<predicate> *schemes){
    if (tokens.at(position).getType() == tokenType::FACTS){
        return;
    }
    schemes->push_back(parseScheme());
    parseSchemeList(schemes);
}

void parser::parseFactList(vector<predicate> *facts){
    if (tokens.at(position).getType() == tokenType::RULES){
        return;
    }
    facts->push_back(parseFact());
    parseFactList(facts);
}

void parser::parseRuleList(vector<rule> *rules){
    if (tokens.at(position).getType() == tokenType::QUERIES){
        return;
    }
    rules->push_back(parseRule());
    parseRuleList(rules);
}

void parser::parseQueryList(vector<predicate> *queries){
    if (tokens.at(position).getType() == tokenType::END){
        return;
    }
    queries->push_back(parseQuery());
    parseQueryList(queries);
}

predicate parser::parseScheme(){
    vector<parameter> params;
    string name;
    if(tokens.at(position).getType() == tokenType::ID){
        name = tokens.at(position).getInput();
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::LEFT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::ID){
        tokenType t = tokens.at(position).getType();
        vector<string> yo;
        string id = tokens.at(position).getInput();
        parameter sis(t, id, yo);
        params.push_back(sis);
        position++;
    }
    else{
        throw tokens.at(position);
    }
parseIdList(&params);
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    predicate schema(name, params);
return schema;
}

predicate parser::parseFact(){
    string name;
    vector<parameter> params;
    if(tokens.at(position).getType() == tokenType::ID){
        name = tokens.at(position).getInput();
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::LEFT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::STRING){
        tokenType t = tokens.at(position).getType();
        vector<string> yo;
        string id = tokens.at(position).getInput();
        parameter sis(t, id, yo);
        params.push_back(sis);
        position++;
    }
    else{
        throw tokens.at(position);
    }
parseStringList(&params);
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::PERIOD){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    predicate fac(name, params);
return fac;
}

rule parser::parseRule(){
    vector<predicate> body;
predicate head = parseHeadPredicate();
    if(tokens.at(position).getType() == tokenType::COLON_DASH){
        position++;
    }
    else{
        throw tokens.at(position);
    }
body.push_back(parsePredicate());
parsePredicateList(&body);
    if(tokens.at(position).getType() == tokenType::PERIOD){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    rule elur(head, body);
return elur;
}

predicate parser::parseQuery(){
predicate queer = parsePredicate();
    if(tokens.at(position).getType() == tokenType::Q_MARK){
        position++;
    }
    else{
        throw tokens.at(position);
    }
return queer;
}

predicate parser::parseHeadPredicate(){
    string name;
    vector<parameter> params;
    if(tokens.at(position).getType() == tokenType::ID){
        name = tokens.at(position).getInput();
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::LEFT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::ID){
        tokenType t = tokens.at(position).getType();
        vector<string> yo;
        string id = tokens.at(position).getInput();
        parameter sis(t, id, yo);
        params.push_back(sis);
        position++;
    }
    else{
        throw tokens.at(position);
    }
parseIdList(&params);
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    predicate head(name, params);
return head;
}

predicate parser::parsePredicate(){
    string name;
    vector<parameter> params;
    if(tokens.at(position).getType() == tokenType::ID){
        name = tokens.at(position).getInput();
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::LEFT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
params.push_back(parseParameter());
parseParameterList(&params);
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    predicate list(name, params);
return list;
}

void parser::parsePredicateList(vector<predicate> *body){
    if (tokens.at(position).getType() == tokenType::PERIOD){
        return;
    }
    if(tokens.at(position).getType() == tokenType::COMMA){
        position++;
    }
    else{
        throw tokens.at(position);
    }
body->push_back(parsePredicate());
parsePredicateList(body);
}

void parser::parseParameterList(vector<parameter> *params){
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        return;
    }
    if(tokens.at(position).getType() == tokenType::COMMA){
        position++;
    }
    else{
        throw tokens.at(position);
    }
params->push_back(parseParameter());
parseParameterList(params);
}

void parser::parseStringList(vector<parameter> *params){
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        return;
    }
    if(tokens.at(position).getType() == tokenType::COMMA){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::STRING){
        tokenType t = tokens.at(position).getType();
        vector<string> yo;
        string id = tokens.at(position).getInput();
        parameter sis(t, id, yo);
        params->push_back(sis);
        position++;
    }
    else{
        throw tokens.at(position);
    }
parseStringList(params);
}

void parser::parseIdList(vector<parameter> *params){
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        return;
    }
    if(tokens.at(position).getType() == tokenType::COMMA){
        position++;
    }
    else{
        throw tokens.at(position);
    }
    if(tokens.at(position).getType() == tokenType::ID){
        tokenType t = tokens.at(position).getType();
        vector<string> yo;
        string id = tokens.at(position).getInput();
        parameter sis(t, id, yo);
        params->push_back(sis);
        position++;
    }
    else{
        throw tokens.at(position);
    }
parseIdList(params);
}

parameter parser::parseParameter(){
    tokenType t = tokens.at(position).getType();
    string thing = tokens.at(position).getInput();
    vector<string> params;
    if(t == tokenType::STRING || t == tokenType::ID){
        position++;
        parameter hey(t, thing, params);
        return hey;
    }
    else if(t == tokenType::LEFT_PAREN){
        params = parseExpression();
    }
    else{
        throw tokens.at(position);
    }
    parameter hey(t, thing, params);
    return hey;
}

vector<string> parser::parseExpression(){
    vector<string> ex;
    if(tokens.at(position).getType() == tokenType::LEFT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
ex.push_back(parseParameter().toString());
ex.push_back(parseOperator());
ex.push_back(parseParameter().toString());
    if(tokens.at(position).getType() == tokenType::RIGHT_PAREN){
        position++;
    }
    else{
        throw tokens.at(position);
    }
return ex;
}

string parser::parseOperator(){
    if (tokens.at(position).getType() == tokenType::ADD){
        position++;
        return "+";
    }
    else if(tokens.at(position).getType() == tokenType::MULTIPLY){
        position ++;
        return "*";
    }
    else{
        throw tokens.at(position);
    }
}