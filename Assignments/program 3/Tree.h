#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  void insertHelper(const string &, Node*); //helper function for insert
  void split(Node*, const string &); 
  void preOrder(Node*) const;
  void inOrder(Node*) const;
  void postOrder(Node* ) const;
  void removeHelper(const string &, Node*); //helper function for removing
  bool searchHelper(const string &, Node*) const;
  Node* searchNode(const string &, Node*); 
  void destructorHelper(Node*)const;
  Tree & operator=(const Tree &) = delete;
  Tree(const Tree &copy) = delete;
  

  
};

#endif