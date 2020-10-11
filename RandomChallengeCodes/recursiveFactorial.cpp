#include <iostream>
#include <stdlib.h>
using namespace std;
double factorial(double n){
    if (n<=1){
        return 1;
    }
    return n*factorial(n-1);
}
int main(int argc, char *argv[]){
    double n = atoi(argv[1]);
    cout << factorial(n) << endl;
    return 0;
}