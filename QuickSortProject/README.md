# Lab5-Quicksort

## Briefing: 
This is a no-help Lab.  This means that you should write and debug the code by yourself (but see the "Exception" below).  If you consult internet resources, you should not look at any code that implements quick sort, though you may consult code in Canvas.  Note, though, that your code must select "the pivot" as described in the lab even though it may be selected differently with other algorithms.

The TAs will be able to help you understand the concepts of the quicksort algorithm (Median of 3 and Partitioning), but they will not be able to answer questions about implementation or help debug your code with you. Help can be given in understanding possible causes of Valgrind and Compilation errors, but the TA will not be able to work with you to solve them. It is OK to work through examples with other students, but you should do the design, implementation, coding and debugging on your own.

## Exception: 
Since this is the first time we will be using destructors in this class, you may get help from TAs and others to properly write your destructor.

## Purpose
The purpose of this lab is to implement quicksort.

## Background
Quicksort is a sorting algorithm developed by Tony Hoare that, on average, makes O(n log n) comparisons to sort n items. It is also known as partition-exchange sort. In the worst case, it makes O(n^2) comparisons, though this behavior is rare. Quicksort is typically faster in practice than other O(n log n) algorithms. Additionally, quicksort's sequential and localized memory references work well with a cache. Quicksort can be implemented as an in-place partitioning algorithm,

## Requirements
You will need the files from this git repository to complete the lab.

### File 1 - Array Tests (10 points)
* This deals with testing operations such as creating and adding to an array. 

### File 2 - Median of Three (20 points)
* It will test your implementation of the median of three function.

### File 3 - Partition (20 points)
* It will test your implementation of the partition function.

### File 4 - Comprehensive Tests & Edge Cases (15 points)
* It will test whether or not your medianOfThree() and partition() functions work on cases that commonly cause problems.

### File 5 - Sort All (25 points)
* It will test whether or not you are able to create your own recursive function using the medianOfThree() and partition() functions you already coded for the previous tests.

### Valgrind (10 points)
* Your solution must be free of memory leaks and other Valgrind errors.

## Requirement Notes
* No predefined data structures may be used for this lab; you must use an array.
* You are required to write a separate '.h' and '.cpp' for every class you implement.
* Please note that because the Test Driver uses random tests, your code will need to be run multiple times to ensure it passes all cases. You must pass each time in order to get full credit for the lab.
