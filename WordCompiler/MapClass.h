#ifndef MAP_CLASS_H
#define MAP_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <map>
#include <list>
#include <set>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;
class MapClass{
public:
    MapClass();
    ~MapClass();
    string removePunct(string text);
    void printVect(vector<string> things, string fileName);
    void produceVect(vector<string> &things, string text);
    void pppSet(string text);
    void printMap(map<string, string> wordmap, string fileName);
    void produceSSmap(vector<string> things, list<string> chungus, string text);


};
#endif