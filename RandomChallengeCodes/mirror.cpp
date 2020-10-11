#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

int main() {
    int tests, row, column;
    string rc;
    vector <string> pic;
    vector<string> rows;
    cin >> tests;
    for(int i = 1; i < tests; i++){
        cin >> row >> column;
        for(int u = 0; u < row; ++u){
            string line;
            cin.ignore();
            getline(cin, line);
            pic.push_back(line);
        }
        cout << "Test " << i << endl;
        for (int o = row; o > 0;){
            stringstream ss(pic.at(o));
            
            for (int u = 0; u < column; u++){
                string thing;
                ss >> thing;
                rows.push_back(thing);
            }
            for (int p = column; p > 1;){
                cout << rows.at(p) << " ";
                p--;
            }
            cout << rows.at(1) << endl;
            o--;
        }
    }
    cout << "no more input" << endl;
    return 0;
}