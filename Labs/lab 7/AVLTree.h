#include "Node.h" 
#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <cstdlib>

using namespace std; 

class AVLTree { 
    private:
      Node *root;
      
    public:
      AVLTree(); //done
      void insert(const string &); //done ish.
      int balanceFactor(Node*) const;  //done 
      void printBalanceFactors() const;   //done?
     // void visualizeTree(const string &);  //not needed
      
    private: 
      void rotate(Node *); 
      void rotateLeft(Node *); //done for now
      void rotateRight(Node *);  //done
      void insert(Node *,Node *); //done pseudocode, fix it.
      void printBalanceFactors(Node *) const; //done
     // void visualizeTree(ofstream &, Node *);  
      int height(Node *) const; //done
      void height(int , int &, Node *) const;   //done
      // void setChild(Node *, string, Node *); 
      // void replaceChild(Node *, Node *,Node *);
};