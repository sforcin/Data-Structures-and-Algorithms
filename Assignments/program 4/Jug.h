#ifndef JUG_H
#define JUG_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Jug {
    public:
        Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
        ~Jug();

        //check inputs, check unsolvable cases
        int solve(string& solution); 
    private:
        // use priority queue instead of trying to create ur own data structure is prob better lol      
        struct State {
            int A, B, cost;
            string steps;

            // Constructor
            State(int a, int b, int c, const string& s) : A(a), B(b), cost(c), steps(s) {}

            bool operator<(const State& other) const { // overload operator  
                return cost > other.cost; // 
            }
        };

        vector<string> visited; // push visited keys into this vector so we can pop it in order. keeps visited states stored in a vector
        int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA; // 9 states given on zybooks, to know we reached the goal.
        
        // to check if goal has been reached
        bool isTarget(int a, int b) const;

        // adds new state to the priority queue.
        void priorityEnqueue(priority_queue<State>& pq, int a, int b, int c, const string& s);
};





#endif  