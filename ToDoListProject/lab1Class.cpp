#include "lab1Class.h"

using namespace std;

    //constructor
lab1Class::lab1Class(){
    ifstream listFile("ToDoList.txt");
        string oldTask;
        while (!listFile.eof()) {       
             getline(listFile, oldTask);
             if (oldTask.length() > 0) {
             ToDoList.push_back(oldTask);
             }
         }
         
    for (int i = 0; i < ToDoList.size(); i++){
        stringstream ss;
        string date;
        string task;
        ss << ToDoList[i];
        ss >> date >> ws;
        getline(ss, task);
        TaskList.push_back(task);
        DateList.push_back(date);
    }
}  
    //destructor
lab1Class::~lab1Class(){}  
    
    /*    *   Adds an item to the todo list with the date specified by the string "_duedate" and the task specified by "_task"   */     
void lab1Class::add(string _duedate, string _task){
    string total;
    total = _duedate + " " + _task;
    TaskList.push_back(_task);
    DateList.push_back(_duedate);
    ToDoList.push_back(total);
    
    
    fstream todoFile;
    todoFile.open("ToDoList.txt", ios::out | ios::trunc);
    for (int i = 0; i < ToDoList.size(); i++){
        todoFile << ToDoList[i] << endl;
    }
    todoFile.close(); 
} 
    
    /*    *   Removes an item from the todo list with the specified task name    *    *   Returns 1 if it removes an item, 0 otherwise    */    
int lab1Class::remove(string _task){
        int position;
        vector<string>::iterator findTask;
        findTask = find(TaskList.begin(), TaskList.end(), _task);
        
        if(findTask != TaskList.end()){
            position = distance(TaskList.begin(), findTask);
            TaskList.erase(findTask);
            DateList.erase(DateList.begin()+position);
            ToDoList.erase(ToDoList.begin()+position);
            
            
            fstream todoFile;
            todoFile.open("ToDoList.txt", ios::out | ios::trunc);
            for (int i = 0; i < ToDoList.size(); i++){
                todoFile << ToDoList[i] << endl;
            }
            todoFile.close();  
        }
        else{
            cout << "This Task is not currently on your List." << endl;
        }
        return 0;
    }    
    
    /*    *   Prints out the full todo list to the console    */    
void lab1Class::printTodoList( ){  
   
    fstream todoFile;
    todoFile.open("ToDoList.txt", ios::out | ios::trunc);
    cout << "All Remaining Tasks: " << endl;
    for (int i = 0; i < ToDoList.size(); i++){
            cout << ToDoList[i] << endl;
            todoFile << ToDoList[i] << endl;
        }
    todoFile.close();  
}
    
    /*    *   Prints out all items of a todo list with a particular due date (specified by _duedate)    */    
void lab1Class::printDaysTasks(string _date){
    int place;
    vector<string>::iterator findDate;
    cout << "Tasks remaining for " << _date << ": " << endl;
    findDate = find(DateList.begin(), DateList.end(), _date);
    for(int i = 0; findDate != DateList.end(); i++){
        place = distance(DateList.begin(), findDate);
        cout << TaskList[place + i] << endl;
        DateList.erase(findDate);
        findDate = find(DateList.begin(), DateList.end(), _date);
    }
}
    
