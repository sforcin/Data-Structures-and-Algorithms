#ifndef __NODE_H__
#define __NODE_H__
#include <string>

using namespace std;

class Node{

    friend class BSTree; // this will give access for this class to have access to the private vars

private:
    Node *left;
    Node *right;
    Node *parent;
    int count;
    string str;

public:
    //create a constructor, destructor, deep copy.
    Node(string);
    Node& operator=(const Node &data);
};




#endif