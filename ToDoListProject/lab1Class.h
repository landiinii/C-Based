#ifndef lab1Class_H
#define lab1Class_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "ToDoListInterface.h"

using namespace std;

class lab1Class : public TodoListInterface{
    protected:
    vector<string> ToDoList;
    vector<string> TaskList;
    vector<string> DateList;
    public:    
    lab1Class(
        //constructor
        );   
    ~lab1Class(
        //destructor
        );    
    
    /*    *   Adds an item to the todo list with the date specified by the string "_duedate" and the task specified by "_task"    */    
    void add(string _duedate, string _task);    
    
    /*    *   Removes an item from the todo list with the specified task name    *    *   Returns 1 if it removes an item, 0 otherwise    */    
    int remove(string _task);    
    
    /*    *   Prints out the full todo list to the console    */    
    void printTodoList();   
    
    /*    *   Prints out all items of a todo list with a particular due date (specified by _duedate)    */    
    void printDaysTasks(string _date);
    
};

#endif
