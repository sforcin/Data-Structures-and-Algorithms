#ifndef WORDENTRY_H
#define WORDENTRY_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class WordEntry {

 private:
	string word;
	int numAppearances;
	int totalScore;
 public:
	WordEntry(const string &, int); //done
	void addNewAppearance(int); //done
	const string & getWord(); //done
	double getAverage(); //done
};
#endif