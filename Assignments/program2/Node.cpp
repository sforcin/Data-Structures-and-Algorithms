#include "Node.h"
#include <iostream>
#include <string>

using namespace std;


Node::Node(string data){
    str = data;
    left =0;
    right =0;
    count =1;
  //  data = "";
}


Node &Node::operator=(const Node& data){

    if(this!=&data){
        this->str = data.str;
        this->count = data.count; 
    }

    return *this;
}

