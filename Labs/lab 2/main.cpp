#include "IntList.h"
#include <iostream>

using namespace std;

int main() {
    //strategy: use push front and push back to build my list, then pop front and back to empty it, then check for segmentation faults. :)
    cout << "Checking all functions work properly:"<<endl;
    IntList test; //i will use this to test my functions
    cout<<"Test inital test: "<<endl;
    cout<<"testing empty function: "<<test.empty()<<endl; //works
    test.push_front(6); //shoul add a 6 in the beginning (only node so far)
    cout<<"testing push_front inserting value 6: "<<test<<endl; //works
    test.push_front(3); //works!
    test.push_front(7); // this goes forward, in front of one. FIX - solved
    cout<<"testing with 7,3,6: "<<test<<endl;
    test.push_back(16);
    test.push_back(10);
    cout << "testing push back, should be 7,3,6,16,10: actual list: "<<test<<endl;
    //now I will test popping functions:
    test.pop_front();
    cout<<"testing pop front function: should be 3,6,16,10: " << test << endl; //works 
    test.pop_front();
    test.pop_front(); //empty existing list
    test.pop_back();
    test.pop_back();//list is empty
    cout << "List is empty, now add values! "<<endl;
    //now that list is empty, i can try adding values.
    test.push_back(4);
    cout<<"Push back in empty list: "<<test<<endl;

    test.push_back(16);
    test.push_back(32);
    cout<<"added 3 values, should be 4, 16, 32: "<<test<<endl;

    cout<<"testing print reverse function: "<<endl; //works as well
    test.printReverse();
    cout<<endl;
    
    cout<<"Print Reverse of empty: ";
    test.pop_back();
    test.pop_back();
    test.pop_back();
    test.printReverse();
    cout << test<<endl;
    cout << "passed all tests."<<endl;

    
    return 0;
}