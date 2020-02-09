# Data Structures

These are some implementation of useful data structures with example programs using them which was given as homeworks for CS-300 course at Sabancı University.There are 4 data structures which is implemented in C++ in this repository.Each file contains data structures and a simple task below in order to show the usage of those data structures(They are simply programs with data structures embeded in).All data structures works error free but they are implemented for the corresponding tasks in the given homeworks.In order to use them for different tasks a little modification might be needed.The data structures are not torn apart from the tasks they are doing for 2 reasons.The first is to demonstrate the use of these data structures, and the second is to prevent students taking this course from easily copying and pasting these data structures and using them for their HW's.

# Files

 * Stack.cpp
 * AVLTree (given as a folder since the program needs some input which is given inside folder as well)
 * HashTable-AVLtree.cpp
 * Heap.cpp
 
## Stack.cpp

Word Processer

This file contains stack data structure implemented in template format.The program basically takes an input from the user with a simple shifted letter combination such as "USer123Alpha4" and does a operations on the string inplace starting from left to right.The operations are done when a number is found in the string.After the operations are done there occurs a meaningful text which is prompt to the user. 

## AVLTree

Dictionary

This folder contains AVLTree.cpp and 4 input files for the user to try the tree.AVLTree.cpp basically contains a templated AVLTree data structure which can be used for holding words and their meanings in order to make the search faster.Users can use this data structure for other purposes such as holding a JSON object etc. after implementing the necessary data structure for the JSON object.

## HashTable-AVLTree.cpp

Dictionary(Same inputs for the AVLTree program but user is prompt with the difference)

This file contains a Hash Table and AVL Tree which is used for same purpose in the above mentioned program.This programs importance was to show the time difference of using a Hash Table vs AVL Tree for the same operations.

## Heap.cpp

Job Scheduling

This file contains Heap data structure with in use of optimizing a simple job scheduling problem.
