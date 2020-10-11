#include "lab1Class.h"

using namespace std;

int main(int argc, char *argv[]) {
    lab1Class run;
    string date;
    string task;
    string command = argv[1];
    if (argc > 1){
        if (command == "add"){
            date = argv[2];
            task = argv[3];
            run.add(date, task);
        }
        else if (command == "remove"){
            task = argv[2];
            run.remove(task);
        }
        else if (command == "printList"){
            run.printTodoList();
        }
        else if (command == "printDay"){
            date = argv[2];
            run.printDaysTasks(date);
        }
    }    
    return 0;
}