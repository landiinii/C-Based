#include "MapClass.h"

using namespace std;

MapClass::MapClass(){};

MapClass::~MapClass(){};

string MapClass::removePunct(string text){
    for (int i = 0, line = text.size(); i < line; i++) 
    { 
        if (!isalpha(text[i])) 
        { 
            text.erase(i--, 1); 
            line = text.size(); 
        }
        else if (text[i] != 'I'){
            text[i] = ::tolower(text[i]);
        }
    } 
    return text;
}

void MapClass::pppSet(string text){
    set<string> seto;
    string file = text + ".txt";
    ifstream input(file.c_str());
    if (input.is_open(), ios::out | ios::trunc){
        while(!input.eof()){
            string word;
            input >> word;
            word = removePunct(word);
            seto.insert(word);
        }
    }
    else {
        cout << "File does not exist!" << endl;
    }
    text = text + "_set.txt";
    fstream setfile(text.c_str(), fstream::in | fstream::out | fstream::trunc);
    for (set<string>::iterator it=seto.begin(); it!=seto.end(); it++) {
        setfile << *it << endl;
    }
    setfile.close();
}

void MapClass::produceVect(vector<string> &things, string text){
    text = text + ".txt";
    ifstream input(text.c_str());
    if (input.is_open()){
        while(!input.eof()){
            string word;
            input >> word;
            word = removePunct(word);
            if (word != " " || word != "  " || word != "   " || word != "\n" || word != "Nephi"){
                things.push_back(word);
            }
        }
    }
    else {
        cout << "File does not exist!" << endl << "Please enter the right name ofr the File: ";
        cin >> text;
    }
}

void MapClass::produceSSmap(vector<string> things, list<string> chungus, string text){
    for(int i = 0; i < things.size(); i++){
        chungus.push_back(things.at(i));
    }
    map<string, string> wordmap;
    string last = "";
    for (list<string>::iterator it=chungus.begin(); it!=chungus.end(); it++) {
        wordmap[last]=*it;
        last = *it;
    }
    printMap(wordmap, text);
}

void MapClass::printVect(vector<string> things, string text){
    fstream vecfile;
    text = text + "_vector.txt";
    vecfile.open(text.c_str(), fstream::out | fstream::trunc);
    for(int i = 0; i < things.size(); i++){
        vecfile << things[i] << endl;
    }
    vecfile.close();
}

void MapClass::printMap(map<string, string> wordmap, string text){
    fstream mapfile;
    text = text + "_1_1.txt";
    mapfile.open(text.c_str(), fstream::in | fstream::out | fstream::trunc);
    for(map<string, string>::iterator it = wordmap.begin(); it != wordmap.end(); it++){
        mapfile << it->first << ", " << it->second << endl;
    }
    mapfile.close();
}
