#include "scanner.h"
#include "parser.h"
#include "interpreter.h"


int main(int argc, char *argv[]){
    string filename;
    if(argc==2){
        filename = argv[1];
    }
    else{
        cout<<"Error: Invalid input argument" << endl;
        return 0;
    }
    try{
        parser run(filename);
        datalogProgram data = run.parseIt();
        interpreter base(data);
    }
    catch(token bad){
        cout << "Failure!" << endl;
        cout << "  (" << bad.toString() << ",\"" << bad.getInput() << "\"," << bad.getLine() << ")";
    }
}