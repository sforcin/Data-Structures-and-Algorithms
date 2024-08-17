#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds
const int NUMBERS_SIZE = 50000;

//add function headers before main function

int genRandInt(int low, int amount); //create a random number

void fillArrays(int arr1[], int arr2[],int arr3[]); //fill in 3 arrays

void Quicksort_midpoint(int numbers[], int i, int k); //this function sorts the given array in the range 
//from i to k using quicksort method. In this function, pivot is the midpoint element (numbers[(i+k)/2]).

/* 
function to find median to adapt to zybooks function
*/
int median(int a, int b, int c);

/* 
this function utilizes different pivot selection technique in quicksort algorithm.
 The pivot is the median of the following three values:
  leftmost (numbers[i]), midpoint (numbers[(i+k)/2]) and rightmost (numbers[k]). 
*/
void Quicksort_medianOfThree(int numbers[], int i, int k);

void InsertionSort(int numbers[], int numbersSize);// this function sorts the given array using InsertionSort method. 

int main() {
    //create 3 arrays rhat we will use for our functions
    int arr[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    //fill arrays w zybook w funcsion
    fillArrays(arr, arr2, arr3);

    clock_t Start = clock(); //start timer
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE); //sort array using quicksort
    clock_t End = clock(); //end timer
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;
    
    Start = clock(); //call start again to measure time again , using same template
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock(); //end timer
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock(); //follow same template again
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;

}


//given
int genRandInt(int low, int amount) {
   return low + rand() % (amount - low + 1);
}

//given 
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    if(i >= k){ //base case
        return;
    }
    int pivot = numbers[i + (k - i) / 2]; //middle of array. 
    int lowIndex = i;
    int highIndex = k;

    bool done = false;
    
    while(!done){ // access entire array
        while(numbers[lowIndex] < pivot){
            ++lowIndex; //low partition
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex; //high partition
        }
        //partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break; //done when they cross
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    // sort lower and higher partition
    Quicksort_midpoint(numbers,i,highIndex);
    Quicksort_midpoint(numbers,highIndex + 1, k);

}

//find the median
int median(int a, int b, int c){
    if(a < b){ 
        if(b < c){
            return b; //b is middle
        }
        else if(a < c){
            return c; //c is middle
        }
        else{
            return a; // a is middle
        }
    }
    else{
        if(a < c){ //repeat to check all possibilities
            return a;
        }
        else if(b < c){
            return c;
        }
        else{
            return b;
        }
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if(i >= k){ //base case, if array is sorted or none to sort
        return;
    }
    int pivot = median(numbers[i], numbers[i + ((k - i) / 2)], numbers[k]); //use median to find the pivot of the array
    int lowIndex = i;
    int highIndex = k; 

    bool done = false;
    
    while(!done){ //loop until one or none elements left
        //increment while the numbers are less than the pivot
        while(numbers[lowIndex] < pivot){
            ++lowIndex;
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex;
        }
        //then partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break;
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    //recursively sort lower and higher partition
    Quicksort_medianOfThree(numbers,i,highIndex);
    Quicksort_medianOfThree(numbers,highIndex + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
    for(int i = 0; i < numbersSize; ++i){ // access all number
        for(int j = i; j < numbersSize; ++j){ // compare with sorted sections
            if(numbers[j] < numbers[i]){ // if out of place 
                int temp = numbers[j];
                numbers[j] = numbers[i]; //swap thm
                numbers[i] = temp;
            }
        }
    }
}
