#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main() {
    
    int hour;
    int min;
    string time;
    string hours;
    string mins;
    cin.clear();
    getline(cin, time);
    stringstream split(time);
    split >> hour;
    split >> min;
    if (min < 45){
        if (hour == 0){
            hour = 23;
        }
        else {
            hour--;
        }
        int flip = 45 - min;
        min = 60 - flip;
    }
    else {
        min = min - 45;
    }
    cout << hour << " " << min;
    return 0;
}