#include "ExpressionManager.h"
#include <sstream>
#include <ctype.h>

using namespace std;

ExpressionManager::ExpressionManager() {}
ExpressionManager::~ExpressionManager() {}

/*
* Checks whether an expression is balanced on its parentheses
*
* - The given expression will have a space between every number or operator
*
* @return true if expression is balanced
* @return false otherwise
*/

vector<string> split(string expression)
{
  stringstream input(expression);
  string token;
  vector<string> things;
  while(getline(input, token, ' '))
  {
    things.push_back(token);
  }
  return things;
}

bool ExpressionManager::isBalanced(string expression){
    stack<char> balance;
    bool response = true;
    stringstream thing(expression);
    for(int i = 0; response && i < expression.length() / 2 + 1; i++){
        char arg;
        thing >> arg;
        if (arg == '{' || arg == '[' || arg == '('){
            balance.push(arg);
        }
        else if (arg == '}' || arg == ']' || arg == ')'){
            if (balance.empty()){
                response = false;
            }
            else{
                char check = balance.top();
                balance.pop();
                if(check == '('){
                    if (arg == '}' || arg == ']'){
                        response = false;
                    }
                }
                else if (check == '['){
                    if (arg == '}' || arg == ')'){
                        response = false;
                    }
                }
                else if (check == '{'){
                    if (arg == ')' || arg == ']'){
                        response = false;
                    }
                }
            }
        }
    }
    if(!balance.empty()){
        response = false;
    }
    return response;
};

/*
* Converts a postfix expression into an infix expression
* and returns the infix expression.
*
* - The given postfix expression will have a space between every number or operator.
* - The returned infix expression must have a space between every number or operator.
* - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix expression.
* otherwise, return the correct infix expression as a string.
*/
string ExpressionManager::postfixToInfix(string postfixExpression){
    stack<string> stack;
    string final;
    if (postfixEvaluate(postfixExpression) != "invalid"){
        vector<string> things = split(postfixExpression);
        for (int i = 0; i < things.size(); i++){
            string result;
            string opt = things.at(i);
            stringstream ss(opt);
            char a;
            bool duble = false;
            while (ss >> a && duble == false){
                if (a == '.'){
                    duble = true;
                }
            }
            ss.clear();
            ss.str(opt);
            ss >> a;
            if (!duble){
                if (isdigit(a)){
                    stack.push(things.at(i));
                }
                else if(stack.size() >= 2) {
                    string opr = stack.top();
                    stack.pop();
                    string opl = stack.top();
                    stack.pop();
                    if (opt == "+"){
                        result = "( " + opl + " + " + opr + " )";
                        stack.push(result);
                    }
                    else if (opt == "-"){
                        result = "( " + opl + " - " + opr + " )";
                        stack.push(result);
                    }
                    else if (opt == "*"){
                        result = "( " + opl + " * " + opr + " )";
                        stack.push(result);
                    }
                    else if (opt == "/"){
                        result = "( " + opl + " / " + opr + " )";
                        stack.push(result);
                    }
                    else if (opt == "%"){
                        result = "( " + opl + " % " + opr + " )";
                        stack.push(result);
                    }
                }
                else {
                    final = "invalid";
                    return final;
                }
            }
            else {
                final = "invalid";
                return final;
            }
        }
        final = stack.top();
        return final;
    }
    else {
        final = "invalid";
        return final;
    }
};

/*
* Evaluates a postfix expression returns the result as a string
*
* - The given postfix expression will have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if postfixExpression is not a valid postfix Expression
* otherwise, return the correct evaluation as a string
*/
string ExpressionManager::postfixEvaluate(string postfixExpression){
    stack<int> stack;
    string final;
    vector<string> things = split(postfixExpression);
    for (int i = 0; i < things.size(); i++){
        int result;
        string opt = things.at(i);
        stringstream ss(opt);
        char a;
        ss >> a;
        if (isdigit(a)){
            int num = stoi(things.at(i));
            stack.push(num);
        }
        else if(stack.size() >= 2) {
            int opr = stack.top();
            stack.pop();
            int opl = stack.top();
            stack.pop();
            if (opt == "+"){
                result = opl + opr;
                stack.push(result);
            }
            else if (opt == "-"){
                result = opl - opr;
                stack.push(result);
            }
            else if (opt == "*"){
                result = opl * opr;
                stack.push(result);
            }
            else if (opt == "/"){
                if (opr != 0){
                    result = opl / opr;
                    stack.push(result);
                }
                else {
                    final = "invalid";
                    return final;
                }
            }
            else if (opt == "%"){
                if (opr != 0){
                    result = opl % opr;
                    stack.push(result);
                }
                else {
                    final = "caution";
                    return final;
                }
            }
        }
        else {
            final = "invalid";
            return final;
        }
    }
    stringstream combine;
    if (stack.size() == 1){
        while(!stack.empty()){
            combine << stack.top();
            stack.pop();
        }
        final = combine.str();
        return final;
    }
    else {
        final = "invalid";
        return final;
    }
};

/*
* Converts an infix expression into a postfix expression
* and returns the postfix expression
*
* - The given infix expression will have a space between every number or operator.
* - The returned postfix expression must have a space between every number or operator.
* - Check lab requirements for what will be considered invalid.
*
* return the string "invalid" if infixExpression is not a valid infix expression.
* otherwise, return the correct postfix expression as a string.
*/
bool processOpt(stack<string> &stack, string &final, string &opt){
    if(stack.empty() || stack.top() == "(" || opt == "("){
        stack.push(opt);
        return true;
    }
    else if (opt == ")"){
        while (stack.top() != "("){
            final = final + stack.top() + " ";
            stack.pop();
            if (stack.empty()){
                return false;
            }
        }
        stack.pop();
        return true;
    }
    else{
        int opPres;
        if (opt == "*" || opt == "/" || opt == "%"){
            opPres = 2;
        }
        else if (opt == "+" || opt == "-"){
            opPres = 1;
        }
        else {
            opPres = 0;
        }
        
        int stPres;
        string top = stack.top();
        if (top == "*" || top == "/" || top == "%"){
            stPres = 2;
        }
        else if (top == "+" || top == "-"){
            stPres = 1;
        }
        else {
            stPres = 0;
        }
        while (opPres <= stPres) {
            final = final + stack.top() + " ";
            stack.pop();
            if(!stack.empty()){
                top = stack.top();
                if (top == "*" || top == "/" || top == "%"){
                stPres = 2;
                }
                else if (top == "+" || top == "-"){
                stPres = 1;
                }
                else {
                stPres = 0;
                }
            }
            else{
                stPres = 0;
            }
        }
        stack.push(opt);
        return true;
    }
}

string ExpressionManager::infixToPostfix(string infixExpression){
    string final;
    stack<string> stack;
    vector<string> things = split(infixExpression);
    for (int i = 0; i < things.size(); i++){
        string opt = things.at(i);
        stringstream ss(opt);
        char a;
        bool duble = false;
        while (ss >> a && duble == false){
            if (a == '.'){
                duble = true;
            }
        }
        ss.clear();
        ss.str(opt);
        ss >> a;
        if (!duble){
            if (isdigit(a)){
                    final = final + opt + " ";
            }
            else if (opt == "(" || opt == ")" || opt == "+" || opt == "-" || opt == "*" || opt == "/" || opt == "%") {
                processOpt(stack, final, opt);
            }
            else {
                    final = "invalid";
                    return final;
            }
        }
        else {
            final = "invalid";
            return final;
        }
    }
    if (!stack.empty()){
        while (stack.size() > 1){
            final = final + stack.top() + " ";
            stack.pop();
        }
        final = final + stack.top();
    }
    vector<string> combo = split(final);
    final = "";
    for (int i = 0; i < combo.size() - 1; ++i){
        final = final + combo.at(i) + " ";
    }
    final = final + combo.back();
    string checkek = postfixEvaluate(final);
    if (checkek != "invalid"){
        return final;
    }
    else {
        final = "invalid";
        return final;
    }
};

