#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"
#include <string>

using namespace std;

class BSTree {
    private:
        Node *root;
      //ENCAPSULATE HELPER FUNCTIONS, NOT BEING USED BY USERS
      Node* search(const string &key, Node*) const;
      void postOrder(Node *) const;
      void preOrder(Node *) const;
      void inOrder(Node *curr) const;
     // void remove(Node *);
    // Node* removeHelper(Node* n, const string &k);


      
    public:
        /* Constructors */
        /* Default constructor */
        BSTree();
        ~BSTree();
        void insert(const string &newString); //DONE
        void remove(const string &key);  //done
      // void remove(Node*& root, const string& key);
        bool search(const string &key) const; //DONE
        string largest() const; //DONE
        string smallest() const; //DONE 
        int height(const string&) const; // DONE
        void destructorHelper(Node*);
        void preOrder() const;
        void postOrder() const;
        void inOrder() const;
        Node* removeHelper(Node* curr, const string &key);
       // Node * removeLeft( Node *curr);
       // Node * removeRight(Node *curr);


};

#endif // __BSTREE_H__