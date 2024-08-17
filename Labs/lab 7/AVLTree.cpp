#include "AVLTree.h"
#include <iostream>
#include <string>

using namespace std;

AVLTree::AVLTree(){
    root =0;
}

void AVLTree::insert(const string &str) {
    Node *newNode = new Node(str); 
    insert(root,newNode);
} 

void AVLTree::insert(Node *curr, Node *newNode) {
   if (!root) {
      root = newNode; 
      root->parent = 0;
      return;
   }
   curr = root;
   while (curr) { 
      if (newNode->str == curr->str) {
          curr->count++; 
          curr = 0;
      } 
      else if (newNode->str < curr->str) {
         if (curr->left == 0) {
            curr->left = newNode;
            newNode->parent = curr;
            curr = 0;
         }
         else
            curr = curr->left;
      }
      else {
         if (curr->right == 0) {
            curr->right = newNode;
            newNode->parent = curr;
            curr = 0;
         }
         else
            curr = curr->right;
      }
   }

  newNode = newNode->parent;
  while (newNode) { 
      rotate(newNode); 
      newNode = newNode->parent; 
      
  }
}


int AVLTree::balanceFactor(Node *curr) const{
    return (height(curr->left)-height(curr->right));
}

void AVLTree::printBalanceFactors() const{
    printBalanceFactors(root);
}

void AVLTree::printBalanceFactors(Node *curr) const{
    if(curr!=nullptr){
        printBalanceFactors(curr->left);
        cout<< curr->str << "("<<balanceFactor(curr) <<"), ";
        printBalanceFactors(curr->right); 
    }
}

int AVLTree::height(Node *curr)const{
    if(curr!=nullptr){
        int heightFinal =0;
        height(0,heightFinal,curr);
        return heightFinal-1;
    }
    else{
        return -1;
    }
}

void AVLTree::height(int count, int &heightFinal, Node *curr) const{
    if(curr!=nullptr){
        count ++;
        if(count >heightFinal){
            heightFinal = count;
        }
        height(count, heightFinal, curr->right);
        height(count, heightFinal, curr->left);
    }
}

void AVLTree::rotate(Node* curr){
    if(balanceFactor(curr) == 2){
        if(balanceFactor(curr->left)==-1){
            rotateRight(curr->left);
        }
    }
    else if(balanceFactor(curr) ==-2){
        if(balanceFactor(curr->right)==1){
            rotateRight(curr->right);
        }
        rotateLeft(curr);
    }
}

void AVLTree::rotateRight(Node *curr) {
    Node *temp = curr->left->right;
    Node *parent = curr->parent;

    if (parent) {
        if (parent->left == curr) {
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }
    } else {
        root = curr->left;
        root->parent = nullptr;
    }

    curr->left->right = curr;
    curr->parent = curr->left;
    curr->left = temp;

    if (temp) {
        temp->parent = curr;
    }
}

void AVLTree::rotateLeft(Node *curr) {
    Node *temp = curr->right->left;
    Node *parent = curr->parent;

    if (parent) {
        if (parent->left == curr) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
    } else {
        root = curr->right;
        root->parent = nullptr;
    }

    curr->right->left = curr;
    curr->parent = curr->right;
    curr->right = temp;

    if (temp) {
        temp->parent = curr;
    }
}


// void AVLTree::setChild(Node *parent, string children, node *child){
//     if(children == "left"){
//         parent->left = data;
//     }
// }



