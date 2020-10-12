#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

enum class tokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END};

class token{
protected:
    tokenType t;
    string input;
    int line;
public:
    token(string value, int spot, tokenType r){
        input=value;
        line=spot;
        t=r;
    }
    ~token(){}
    string toString();
    int getLine();
    string getInput();
    tokenType getType();
};

#endif