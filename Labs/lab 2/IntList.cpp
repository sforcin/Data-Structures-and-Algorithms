#include <iostream>
#include "IntList.h"

using namespace std;

IntList::IntList(){

// since these are dummy nodes, we have to first allocate memory for them within our list, then
//establish a prev and next for them.
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    
}
//I will start by doing the easiest functions that I know how to do, thats why they are not in order


bool IntList::empty() const{
    //try to use the method the professor introduced in class, returning this will return true or false.
    return (dummyHead->next == dummyTail); 
}

void IntList::push_back(int value){
    //start off with edge cases, if list is empty, create new node
    //prof said in class that we can call isEmpty function here instead of checking it again.

    IntNode *temp = new IntNode(value); // in order to add a node to the end of the list, the node needs to exist first
    //edge case:
    if(dummyHead==nullptr){ //list is empty
        dummyHead = temp;
        dummyTail = temp;
    }
    else{
        temp->prev =dummyTail->prev;
        temp->next = dummyTail;
        dummyTail->prev->next =temp;
        dummyTail->prev=temp;
    }
}


void IntList::pop_back(){
    //we need to do a similar process from push back, but without assigning new value to tail
    //if list is empty, do we return an error and break out of function? throw an exception...?
    //IntNode *temp = new IntNode(data);
    if(dummyHead == nullptr){
        throw std::runtime_error("List is empty, cannot perform pop_back");  // Throw an exception
    }
    else{
        IntNode* temp = dummyTail->prev; // create a new temp pointer that points to last node before tail
        dummyTail->prev = temp->prev; //makes the previous node before tail point to node before temp
        temp->prev->next = dummyTail; // makes temp point to the nail using the prev and next, so we can delete the tail
        delete temp; // we made temp point to the tail, so we can delete it without having to alter the actual tail, almost like working around the tail
        
    }

}


IntList::~IntList(){ //destructor
    while(dummyHead->next!= nullptr){ //while the list is not empty
        IntNode *temp = dummyHead->next->next;//creating a new node pointng to node after the head
        dummyHead->next = temp; //node after the head will be temp
        delete dummyHead->next; //deleting one node after the head, still keeping the one after it
    }
    delete dummyHead; //deleting the head
}

void IntList::push_front(int value){
    IntNode *temp = new IntNode (value);

    if(dummyHead == nullptr){
        dummyHead = temp;
        dummyTail = temp;
    }

    else{
        temp->next = dummyHead->next;
        temp->next->prev=temp;
        dummyHead->next = temp; 
        temp->prev = dummyHead;
    }  


}

void IntList::pop_front(){
    // edge cases: check if list is empty and if there is only one node 
    // IntNode *temp = new IntNode;
    if(dummyHead == nullptr){
        throw std::runtime_error("List is empty, cannot perform pop_front");  // Throw an exception
    }
    else{

        IntNode *temp = dummyHead->next; 
        dummyHead->next = temp->next;
        temp->next->prev = dummyHead;  
        delete temp; 
    }
} 




ostream& operator<<(std::ostream &out, const IntList &rhs) {
   // IntNode *temp = rhs.dummyHead; 
    if(rhs.dummyTail != rhs.dummyHead->next){
        for (IntNode* curr = rhs.dummyHead->next; curr != rhs.dummyTail->prev; curr = curr->next){
            out << curr->data << ' ';
        }
        out << rhs.dummyTail->prev->data;
    }
    return out;
}

void IntList::printReverse() const {

    if(dummyTail != dummyHead->next)
    {
        for (IntNode* curr = dummyTail->prev; curr != dummyHead->next; curr = curr->prev)
        {
            cout << curr->data << ' ';
        }
        cout<<dummyHead->next->data;
    }
}


