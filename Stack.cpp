//
//  main.cpp
//  CS-300#HW1
//
//  Created by Onur Arda Bodur on 10.03.2019.
//
/*
 
 Name:Onur Arda
 Surname:Bodur
 ID:23617
 
 - CS300 – Spring 2018-2019 -
 - Sabancı University Homework #1 -
 – The Word Processor -
   March 12t​h​ Tuesday 22:00
 NOTE:One day late submit allowed with
 */

#include <iostream>
#include <string>
#include <stack>

using namespace std;

template <class Object> //Class defined for the Stack
class Stack {
public:
    
    Stack();
    
    Stack(const Stack & rhs) ;
    
    ~Stack() ;
    
    bool isEmpty() const ; //checks whether stack is empty or not if empty returns true
    
    void makeEmpty() ;
    
    void pop()  ; //pops out the top of the stack
    
    void push(const Object & x) ;//pushes in to the top of the stack
    
    Object TopAndPop() ;
    
    const Object & top() const ; //allows you to check the top of your stack
    
    const Stack & operator=(const Stack & rhs) ; //copy constructor
    
private:
    
    struct ListNode{ //node for the stack
        
        Object element ; //any object that it can carry
        
        ListNode *next ; //holds the address of the next node
        
        ListNode( const Object & theElement, ListNode * n = nullptr )
        
        : element( theElement ), next( n ) { }
        
    };
    
    ListNode *topOfStack; // list itself is the stack
    
};

template <class Object>
Stack<Object>::Stack(){
    
    topOfStack = nullptr; //constructor
    
}

template <class Object>
bool Stack<Object>::isEmpty() const {
    
    if (topOfStack==nullptr) { //if the topOfStack is nullptr,it means that Stack is empty
        return true;
    }
    else
        return false;
    
}



template <class Object>
const Object & Stack <Object> ::top() const {
    
    if (isEmpty()) {
        // throw Underflow();
    }
    
    return topOfStack->element;
    
}

template <class Object>
void Stack<Object> :: pop( )  {
    
    if (isEmpty()) {
        //throw Underflow();
    }
    
    ListNode * oldTop = topOfStack;
    
    topOfStack = topOfStack->next;
    
    delete oldTop;
    
}

template <class Object>
void Stack <Object> :: push(const Object & x){
    
    topOfStack = new ListNode (x,topOfStack); //creates a new node and adds it to the top which makes it top
    
}

template <class Object>
Object Stack<Object>::TopAndPop(){
    
    Object topItem = top();
    pop();
    return topItem;
    
}

template <class Object>
void Stack<Object>::makeEmpty(){
    
    while (!isEmpty())
        
        pop();
    
}

template <class Object>
const Stack <Object> & Stack<Object>::operator=(const Stack<Object> &rhs) {
    
    if (this != & rhs) {
        
        makeEmpty();
        
        if (rhs.isEmpty()) {
            
            return * this;
            
        }
        
        ListNode * rptr = rhs.topOfStack;
        
        ListNode * ptr = new ListNode(rptr->element);
        
        topOfStack = ptr;
        
        for (rptr = rptr->next; rptr != nullptr; rptr=rptr->next) {
            
            ptr = ptr->next = new ListNode(rptr->element);
        }
        
        return *this;
    }
}

template <class Object>
Stack<Object>::Stack(const Stack<Object> & rhs){
    
    topOfStack = nullptr ;
    
    *this = rhs ;
    
}

template <class Object>
Stack<Object>::~Stack(){ //manually defined destructor
    
    makeEmpty();

    
}


int main(){
    
    cout << "Input:";
    
    string input;
    
    cin >> input;
    
        Stack<string>stack_main;
    
        Stack<string>stack_taker;
    
        Stack<string>stack_rest;
    
        Stack<string>stack_rest_for_operation_3;
    
        Stack<string>stack_rest_for_operation_5_1;
    
        Stack<string>stack_rest_for_operation_5_2;
    
        Stack<string>stack_rest_for_operation_6;
    
    
    //In this part of the program,the loops under this statement takes the input given and puts them into the stack taker
    //After the input is pushed into the stack taker it is reversed for the operations necessary
    //The reversed stack is named stack main
    
                for (int i = 0; i<input.size(); i++) {
                    stack_taker.push(input.substr(i,1));
                }
    
                    while (!stack_taker.isEmpty()) {
                        stack_main.push(stack_taker.top());
                        stack_taker.pop();
                    }
    
    int sizer=0;
    unsigned long sizer_3_4=0;
    string operator_for_3_4;
    
    for (int i = 0; i<input.size(); i++){
        if (!stack_main.isEmpty()) { //if main contains info the program works
    
            if (stack_main.top()!="1" && stack_main.top()!="2" && stack_main.top()!="3"&& stack_main.top()!="4"&&stack_main.top()!="5"&&stack_main.top()!="6") { //if the element in the input is an letter it is pushed to the stack rest
            
                stack_rest.push(stack_main.top());
                
                stack_main.pop();
                
                sizer++;
            }
            else{
                
                if (stack_main.top()=="1") { //if the element in the input is 1 program 'Ends'
                    while (!stack_rest_for_operation_3.isEmpty()) { //before breaking the loop puts the info in the right of the cursor
                        stack_rest.push(stack_rest_for_operation_3.top());
                        stack_rest_for_operation_3.pop();
                    }
                    break; //breaks the loop
                }
                
                else if (stack_main.top()=="2") { //if the element in the input is 2 the last element on the stack rest is deleted
                    if (!stack_rest.isEmpty()) //changed************
                        stack_rest.pop();
                    
                    stack_main.pop();
                    sizer--;
                }
                else if (stack_main.top()=="3"||stack_main.top()=="4"){ //if the element in the input is 3 or 4 the cursor is changed
                    if (stack_main.top()=="3") { //moves the cursor to the left
                        stack_main.pop();
                        stack_rest_for_operation_3.push(stack_rest.top());  //the right of the cursor is in stack rest for operation
                        stack_rest.pop(); //left of the cursor
                    } else if(stack_main.top()=="4") { //moves the cursor to the right
                        stack_main.pop();
                       if (!stack_rest_for_operation_3.isEmpty()) { //changed************
                            stack_rest.push(stack_rest_for_operation_3.top()); // the left of the cursor is in stack rest
                            stack_rest_for_operation_3.pop();
                        }
                        
                    }
                }
                else if (stack_main.top()=="5") { //reverses the elements on the left of the cursor
                    stack_main.pop();
                   
                    while(!stack_rest.isEmpty()){
                        stack_rest_for_operation_5_1.push(stack_rest.top());
                        stack_rest.pop();
                    }
                    
                    while(!stack_rest_for_operation_5_1.isEmpty()){
                        stack_rest_for_operation_5_2.push(stack_rest_for_operation_5_1.top());
                        stack_rest_for_operation_5_1.pop();
                    }
                    
                    while(!stack_rest_for_operation_5_2.isEmpty()){
                        stack_rest.push(stack_rest_for_operation_5_2.top());
                        stack_rest_for_operation_5_2.pop();
                    }
                    
                }
                else if (stack_main.top()=="6") { //if 6 is given as an input the next element after it is important
                    stack_main.pop(); //6 popped out
                    string deleter=stack_main.top(); //the element after 6
                    stack_main.pop(); //that element also popped out
                    Stack<string> reversed; // a reverser stack
                    int size=0;
                    while (!stack_rest.isEmpty()) {
                        reversed.push(stack_rest.top());
                        stack_rest.pop();
                        size++;
                    }
                    while (!reversed.isEmpty()) {
                        stack_rest.push(reversed.top());
                        reversed.pop();
                    }
                    for (int i = 0; i<size; i++) {
                      
                        if (stack_rest.top()==deleter) { //if the top of the stack is element to be deleted
                            stack_rest.pop(); //it is only popped out
                        }
                        else{ // if the top of the stack is not the element to be deleted
                            stack_rest_for_operation_6.push(stack_rest.top());//it is pushed to the stack
                            stack_rest.pop();
                        }
                    }
                    while (!stack_rest_for_operation_6.isEmpty()) { //after the stack is cleared from the deleted letters
                        
                        stack_rest.push(stack_rest_for_operation_6.top()); //stack is reversed
                        stack_rest_for_operation_6.pop();
                    }
                }
                sizer=0;
            }
        }
        else{ //if the main is empty the program does not work
            break;
            }
        }
  
    stack<string>reverser;
    
    while (!stack_rest.isEmpty()) { //This part is for reversing the final stack that has been word processed
        reverser.push(stack_rest.top());
        stack_rest.pop();
    }
    
    cout << "Output:";
    
    while (!reverser.empty()) { //This part is for printing the stack
        cout << reverser.top();
        reverser.pop();
    }
    
    cout<< endl;
    
    return 0;
}
