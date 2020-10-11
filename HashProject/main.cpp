#include <iostream>
#include <time.h>

// TODO: include the appropriate library for that class
#include <set>
#include "Hash.h"    // this was the name of my header file for my hash set class
#include <unordered_set>

using namespace std;

// takes as input the number of items to insert into the set
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments" << endl;
        return 0;
    }
    
    int N = atoi(argv[1]);  // store the number of items to be put into the set into the integer N
    
    // store N random integers into an array
    int *insertNums = new int[N];
    for (int i = 0; i < N; i++) {
        insertNums[i] = rand() % 99999;
    }

    long empieza, fin;
    

    // instantiate a set object;
    //set<int> *s = new set<int>;
    //unordered_set<int> *s = new unordered_set<int>;
    Hash *s = new Hash(N);

    cout << "Insert " << N << " integers into from the SET ... ";
    empieza = clock();

    for (int i = 0; i < N; i++) {
        s->insert(insertNums[i]);
        //cout << s->size() << endl;
    }

    fin = clock();
    
    cout << "done" << endl;
    cout << "Processor time elapsed to insert " << N << " items: " << (fin - empieza) << endl << endl << endl;

    //s->Print();

    cout << "Remove " << N << " integers into from the SET ... ";
    empieza = clock();

    for (int i = 0; i < N; i++) {
        s->erase(insertNums[i]);
    }

    fin = clock();
    
    cout << "done" << endl;
    cout << "Processor time elapsed to remove " << N << " items: " << (fin - empieza) << endl << endl << endl;
    
    delete[] insertNums;
    delete s;

    return 0;
}