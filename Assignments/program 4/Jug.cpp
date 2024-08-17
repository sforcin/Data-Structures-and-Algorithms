#include "Jug.h"
#include <algorithm>

using namespace std;

//parameterized constructor
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) 
        : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}

Jug::~Jug() {}

//function to know if we reached the goal of program
bool Jug::isTarget(int a, int b) const {
    return (a == 0 && b == N); //a is empty, b is filled to goal amount. 
}

//use priority queue for this.
void Jug::priorityEnqueue(priority_queue<State>& prior, int a, int b, int c, const string& s) {
    if (a >= 0 && b >=0 && a <= Ca && b <= Cb) { 
		string state = to_string(a) + "," + to_string(b); // create the pq

		if (find(visited.begin(), visited.end(), state) == visited.end()) { // check if state has been visited
			visited.push_back(state); // if yes, push into 
			prior.push(State(a, b, c, s)); // pushes the new state onto priority queue
		}
	}
}

int Jug::solve(string& solution) {
    // unsolvable cases first. 
    solution = "";

    if (N > Ca + Cb) return -1; // if goal is greater than both jugs combined

    if (N > Cb) return -1; // if goal is greater than capacity of Jug B

    if (Ca == 0 && Cb != N) return -1; // A is at 0 and B is not at goal

    if (Cb == 0 && Ca != N) return -1; // B is at 0 and A is not the capacity

    if (Ca < 0 || Cb < 0 || N < 0 || ceB < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0 ) return -1; // if any input is negative

    if (Ca > 1000 || Cb > 1000) return -1; // if capacities are too high
//end of unsolvable cases
    // Diijkstra's Algorithm
    priority_queue<State> prior;
    visited.clear(); //clear visited so we can push things into it

    prior.push(State(0, 0 , 0, "")); //set the initial values to that
    visited.push_back("0,0"); //we start at the origin

    while (!prior.empty()) { //means we are at the end of the path
        State curr = prior.top();
        prior.pop();

        int a = curr.A; //prof notes during office hours
        int b = curr.B;
        int cost = curr.cost;
        string steps = curr.steps;

        if (isTarget(a, b)) { //if we reached our targer
            solution = steps + "success " + to_string(cost); //output amount of steps it took to get to get to end of path
            return 1;
        }

        // Fill A
		priorityEnqueue(prior, Ca, b, cost + cfA, steps + "fill A\n"); //steps given during office hours

		// Fill B
		priorityEnqueue(prior, a, Cb, cost + cfB, steps + "fill B\n"); //follow the algorithm to find shortest path 

		// Empty A
		priorityEnqueue(prior, 0, b, cost + ceA, steps + "empty A\n");

		// Empty B
		priorityEnqueue(prior, a, 0, cost + ceB, steps + "empty B\n");

		//  A to B
		int pourAB = min(a, Cb - b);
		priorityEnqueue(prior, a - pourAB, b + pourAB, cost + cpAB, steps + "pour A B\n");

		//  B to A
		int pourBA = min(b, Ca - a);
		priorityEnqueue(prior, a + pourBA, b - pourBA, cost + cpBA, steps + "pour B A\n");
    }

    solution = ""; 
    return 0;
}

//try to do it the way prof did it, using graphs after due date