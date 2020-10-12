#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"
#include <fstream>
#include <cctype>
#include <stack>


class scanner{
protected:
    ifstream file;
    int cline = 1;
    vector<token> snekot;
public:
    scanner(string filename){
        file.open(filename, ifstream::in);
        if (file.is_open()){
            scanit();
        }
    }
    ~scanner(){
        //printit();
        file.close();
    }
    void scanit();
    //void printit();
    token letters(string start);
    void comment(string start);
    token blockcomm(string start);
    token stringy(string start);
    
    
    
    token getToken(int pos);
    int getTokenSize();
};

#endif