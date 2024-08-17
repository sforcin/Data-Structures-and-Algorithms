#include "Heap.h"
#include <iostream>

using namespace std;

// Constructor initializes the heap with zero items.
Heap::Heap(){
    numItems = 0;
}

// Enqueue a PrintJob into the heap while maintaining the heap property.
void Heap::enqueue(PrintJob* job){
    if(numItems < MAX_HEAP_SIZE){
        // Add the new job to the end of the heap array.
        arr[numItems++] = job;
        
        // Restore the heap property by swapping elements until the heap property is restored.
        int currIndex = numItems - 1;
        while(arr[0] != job && arr[(currIndex - 1) / 2]->getPriority() < arr[currIndex]->getPriority()){
            PrintJob* temp = arr[(currIndex - 1) / 2];
            arr[(currIndex - 1) / 2] = arr[currIndex];
            arr[currIndex] = temp;
            currIndex = (currIndex - 1) / 2;
        }
    }
}

// Dequeue the highest priority PrintJob from the heap and adjust the heap.
void Heap::dequeue(){
    if(numItems > 1){  
        // Swap the first and last elements and decrement the number of items.
        PrintJob* temp = arr[0];
        arr[0] = arr[numItems - 1];
        arr[numItems - 1] = temp;
        numItems--;

        // Restore the heap property by trickling down the root element.
        trickleDown(0);
    }
}

// Adjust the heap by trickling down the element at the given index.
void Heap::trickleDown(int i){
    PrintJob* temp;
    while(i < (numItems - 1) / 2 && ( arr[i]->getPriority() < arr[2*i + 1]->getPriority() || arr[i]->getPriority() < arr[2*i + 2]->getPriority())){
        // Swap with the larger child to maintain the heap property.
        if(arr[2*i + 1]->getPriority() > arr[2*i + 2]->getPriority()){
            temp = arr[i];
            arr[i] = arr[i * 2 + 1];
            arr[i * 2 + 1] = temp;
            i = i * 2 + 1;
        }
        else{
            temp = arr[i];
            arr[i] = arr[i * 2 + 2];
            arr[i * 2 + 2] = temp;
            i = i * 2 + 2;
        }
    }
}

// Get the highest priority PrintJob in the heap (root).
PrintJob* Heap::highest (){  
    if (numItems > 0){
        return arr[0];
    }
    else{
        return nullptr;
    }
}

// Print the details of the highest priority PrintJob in the heap.
void Heap::print(){
    cout << "Priority: " << arr[0]->getPriority();
    cout << ", Job Number: " << arr[0]->getJobNumber();
    cout << ", Number of Pages: " << arr[0]->getPages() << endl;
}
