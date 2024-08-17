
#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

struct Node { 

  friend class Tree;

    string small;
    string large;
    int count; 

    Node *left;
    Node *middle;
    Node *right;
    Node *parent;


    Node (const string& key)  
    :
    small(key),
    large(""), 
    count(1),
    left(nullptr),
    middle(nullptr),
    right(nullptr),
    parent(nullptr)
    {
    } 


};

#endif