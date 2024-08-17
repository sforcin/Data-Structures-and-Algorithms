#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

//given
vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

//we will use templates in order to be able to manipulate vectors of all types
template <class T> unsigned min_index(const vector<T> &vals, unsigned index){
    unsigned minValue= index;
    for(int i=index;i<int(vals.size());i++){
        if(vals.at(i)<vals.at(minValue)){
            minValue=i;
        }
    }
    return minValue;
}
/* I was getting an error in this part, 
so i had to move function up in order so it works
*/

template <class T> T getElement(vector<T> vals, int index){
   if(int(vals.size())<index){
    throw out_of_range("Invalid: out of bounds");
   }
   return vals.at(index);
   //we will write the try and throw in the main function, not here
}

template <class T> void selection_sort(vector <T> &vals){
    //step 1: write a for loop accessing all items of vald
    unsigned min;
    for(unsigned i=0; i<vals.size();++i){
        min = min_index (vals,i);
        swap(vals.at(min),vals.at(i));//memorize as many sorting algorithms as u csn
    }
}



int main(){
    //part A: test to see if both functions work properly

    vector <int> test{2,4,6,8,6,7,5};
    selection_sort<int>(test);

    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }

    return 0;
}

