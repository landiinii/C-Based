# Lab3-Expressions
## Purpose
To become familiar with the use of stacks as data structures.

A short video has been created for this lab which you may find very helpful.  You can watch it 
[here](https://youtu.be/HJOnJU77EUs).

## Background
Develop an Expression Manager that performs several operations on infix and postfix expressions. Be able to convert from one form to the other, evaluate postfix expressions, and check for balanced parenthetical expressions.

You may also refer to Edsger Dijkstra's "Shunting-yard algorithm" for additional help, which can be viewed 
[here](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).



## Requirements
Details for method constraints are found in these documents and are still a part of the requirements.

You will need the files in this git repository to complete this assignment.
Extend the ExpressionManagerInterface.h.

### File 1 - Balanced Symbols Check (20 points)
* Determine whether an expression is balanced. { [ } ] is not balanced. [ ( ) ] is balanced and valid

### File 2 - Postfix Expression Evaluation (20 points)
* Determine if the given postfix expression is valid
* Evaluate the given postfix expression
* Handle attempts to divide by 0

### File 3 - Postfix to Infix Conversion (30 points)
* Determine if the given postfix expression is syntactically valid
* Convert the postfix expression into an infix expression

### File 4 - Infix to Postfix Conversion (30 points)
* Determine if the given infix expression is syntactically valid
* Convert the infix expression into a postfix expression

## Requirement Notes
* You are required to create a seperate '.cpp' and '.h' for each class you implement for this lab.
* Valid expressions consist of integers; brackets, braces, and parentheses; and +, -, *, /, and %. Reject any invalid expressions.
* Your calculations should perform integer divison and produce integer results
* Valid expressions also need to satisfy standard infix or postfix requirements
* {,},(,),[, and ] are the only symbols considered for the Balanced Symbols Check
* You can assume there will be a space between every number or operator
* You must put parenthesis '()' around every part of the expression during the postfix to infix conversion. i.e. "4 2 5 + *" = "( 4 * ( 2 + 5 ) )"
* You must use the stack class pre-defined in the C++ Standard Template Library (STL). i.e. #include <stack>
* You can use the examples in this git repository 
