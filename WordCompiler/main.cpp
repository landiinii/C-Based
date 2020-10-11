#include "MapClass.h"

using namespace std;


int main(int argc, char *argv[]) {
    MapClass start;
    vector<string> things;
    list<string> chungus;
    string text = argv[1];
    int M = 3;
    int L = atoi(argv[2]);
    start.pppSet(text);
    start.produceVect(things, text);
    start.printVect(things, text);
    //start.produceSSmap(things, chungus, text);
    
    
    map<list<string>, vector<string> > wordmap;
    list<string> state;
    srand(time(NULL));
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for (vector<string>::iterator it=things.begin(); it!=things.end(); it++) {
        wordmap[state].push_back(*it);
        state.push_back(*it);
        state.pop_front();
    }
    state.clear();
    for (int i = 0; i < M; i++) {
        state.push_back("");
    }
    for(int i = 0; i < L; i++){
        int in = rand();
        int ind;
        if (wordmap[state].size() <= 0) {
            ind = in;
        }
        else {
            ind = in % wordmap[state].size();
        }
        cout << wordmap[state][ind]<<" ";
        state.push_back(wordmap[state][ind]);
        state.pop_front();
    }
    cout << endl;
    
    return 0;
}