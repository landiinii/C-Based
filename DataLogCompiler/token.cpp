#include "token.h"

tokenType token::getType(){
    return t;
}

string token::toString(){
    switch(t){
        case tokenType::COMMA:
            return "COMMA";
            break;
        case tokenType::PERIOD:
            return "PERIOD";
            break;
        case tokenType::Q_MARK:
            return "Q_MARK";
            break;
        case tokenType::LEFT_PAREN:
            return "LEFT_PAREN";
            break;
        case tokenType::RIGHT_PAREN:
            return "RIGHT_PAREN";
            break;
        case tokenType::COLON:
            return "COLON";
            break;
        case tokenType::COLON_DASH:
            return "COLON_DASH";
            break;
        case tokenType::MULTIPLY:
            return "MULTIPLY";
            break;
        case tokenType::ADD:
            return "ADD";
            break;
        case tokenType::SCHEMES:
            return "SCHEMES";
            break;
        case tokenType::FACTS:
            return "FACTS";
            break;
        case tokenType::RULES:
            return "RULES";
            break;
        case tokenType::QUERIES:
            return "QUERIES";
            break;
        case tokenType::ID:
            return "ID";
            break;
        case tokenType::STRING:
            return "STRING";
            break;
        case tokenType::COMMENT:
            return "COMMENT";
            break;
        case tokenType::UNDEFINED:
            return "UNDEFINED";
            break;
        case tokenType::END:
            return "EOF";
            break;
        default:
            return "Uhh Ohh";
    }
}

string token::getInput(){
    return input;
}

int token::getLine(){
    return line;
}