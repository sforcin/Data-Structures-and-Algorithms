#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template <typename T> 
class stack{
    private:
    int MAXSIZE = 20;
    T data[20]; // use template type T for array, since it could be filled with integers or strings
    int size;

    public:
    //constructor: initializing size to 0.
    stack():size(0){};

    //void function: I checked if array is empty, if not, 
    //just go to the next open spot of the stack, and assign that spot to the new value
    void push(T val){
        if(size==20){
            throw overflow_error("Called push on full stack.");
        }
        data[size++]=val;
    }

    //check if size is 0, if not, return what ever is in the location of size, then decrease size by using --
    T pop(){
        if(size==0){
            throw out_of_range("Called pop on empty stack.");
        }
        return data[size--];
    }

//checking if stack is empty
    bool empty(){
        return(size==0);
    }

/* i first checked if stack is empty or if it has only 1 item.
    if not, i called the original pop() function twice, since it handles exceptions,
    and pops one value from the stack
*/
    void pop_two(){
        if(size==0){
            throw out_of_range("Called pop_two on empty stack.");
        }
        if(size==1){
            throw out_of_range("Called pop_two on a stack of size 1.");
        }
        pop(); // when calling this function twice, it will automatically check once again if array is empty
        pop();
    }

    // check for exceptions, if not, the item on top of the stack will be located at size-1,
    // since we are using the template, the return will work for all types
    T top(){
        if(size==0){
            throw underflow_error("Called top on empty stack.");
        }
        return data[size-1];
    }
};

#endif