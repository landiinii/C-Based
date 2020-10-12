#include "scanner.h"


void scanner::scanit(){
    char c;
    while(file.peek() != EOF){
        c = file.get();
        string in(1, c);
        if(isspace(c)){
                if(c == '\n'){
                    cline++;
                }
        }
        else if(isalpha(c)){
                token letty = letters(in);
                snekot.push_back(letty);
        }
        else{
            switch(c){
                case ',': {
                        token comma(in, cline, tokenType::COMMA);
                        snekot.push_back(comma);
                    }
                    break;
                case '.': {
                        token period(in, cline, tokenType::PERIOD);
                        snekot.push_back(period);
                    }
                    break;
                case '?': {
                        token qmark(in, cline, tokenType::Q_MARK);
                        snekot.push_back(qmark);
                    }
                    break;
                case '(': {
                        token lparen(in, cline, tokenType::LEFT_PAREN);
                        snekot.push_back(lparen);
                    }
                    break;
                case ')': {
                        token rparen(in, cline, tokenType::RIGHT_PAREN);
                        snekot.push_back(rparen);
                    }
                    break;
                case '*': {
                        token multiply(in, cline, tokenType::MULTIPLY);
                        snekot.push_back(multiply);
                    }
                    break;
                case '+': {
                        token add(in, cline, tokenType::ADD);
                        snekot.push_back(add);
                    }
                    break;
                case ':': {
                        if(file.peek() == '-'){
                            string dash(1, file.get());
                            token coldash(in + dash, cline, tokenType::COLON_DASH);
                            snekot.push_back(coldash);
                        }
                        else{
                            token colon(in, cline, tokenType::COLON);
                            snekot.push_back(colon);
                        }
                    }
                    break;
                case '#': {
                        if (file.peek() == '|'){
                            token blcom = blockcomm(in);
                            if(blcom.toString() == "UNDEFINED"){
                                snekot.push_back(blcom);
                            }
                        }
                        else{
                            comment(in);
                        }
                    }
                    break;
                case '\'': {
                        token stri = stringy(in);
                        snekot.push_back(stri);
                    }
                    break;
                default: {
                        token undie(in, cline, tokenType::UNDEFINED);
                        snekot.push_back(undie);
                    }
            }
        }
    }
    token endie("", cline, tokenType::END);
    snekot.push_back(endie);
}

token scanner::letters(string start){
    stringstream ss;
    ss << start;
    while(isalnum(file.peek())){
        string brice(1, file.get());
        ss << brice;
    }
    string word = ss.str();
    tokenType t;
    if(word.compare("Schemes") == 0){
        t = tokenType::SCHEMES;
    }
    else if(word.compare("Facts") == 0){
        t = tokenType::FACTS;
    }
    else if(word.compare("Rules") == 0){
        t = tokenType::RULES;
    }
    else if(word.compare("Queries") == 0){
        t = tokenType::QUERIES;
    }
    else{
        t = tokenType::ID;
    }
    token letta(word, cline, t);
    return letta;
}

void scanner::comment(string start){
    while(file.peek() != '\n'){
        file.get();
    }
}

token scanner::blockcomm(string start){
    stringstream ss;
    string yo(1, file.get());
    ss << start << yo;
    int first = cline;
    char c = file.get();
    bool ender = true;
    if (c == '|'){
        if(file.peek() == '#'){
            ender = false;
        }
    }
    while(ender){
        if(c == '\n'){
            cline++;
        }
        if(file.peek() == EOF){
            string ho(1, c);
            ss << ho;
            token haha(ss.str(), first, tokenType::UNDEFINED);
            return haha;
        }
        else{
            string brice(1, c);
            ss << brice;
        }
        c = file.get();
        if (c == '|'){
            if(file.peek() == '#'){
                ender = false;
            }
        }
    }
    string slash(1, c);
    string hashtag(1, file.get());
    ss << slash << hashtag;
    token letta(ss.str(), first, tokenType::COMMENT);
    return letta;
}

token scanner::stringy(string start){
    stringstream ss;
    ss << start;
    int first = cline;
    char c = file.get();
    while(c != '\'' || file.peek() == '\''){
        if(c == '\n'){
            cline++;
        }
        if(file.peek() == EOF){
            string ho(1, c);
            ss << ho;
            token haha(ss.str(), first, tokenType::UNDEFINED);
            return haha;
        }
        if(c=='\'' && file.peek()=='\''){
            string apost(1, c);
            string aposto(1, file.get());
            ss << apost << aposto;
        }
        else{
            string brice(1, c);
            ss << brice;
        }
        c = file.get();
    }
    string slash(1, c);
    ss << slash;
    token letta(ss.str(), first, tokenType::STRING);
    return letta;
}

/*void scanner::printit(){
    int size = snekot.size();
    for(int i=0; i<size; ++i){
        token temp = snekot.at(i);
        cout << "(" << temp.toString() << ",\"" << temp.getInput() << "\"," << temp.getLine() << ")" << endl;
    }
    cout << "Total Tokens = " << size;
}*/

token scanner::getToken(int pos){
    return snekot.at(pos);
}
int scanner::getTokenSize(){
    return snekot.size();
}
