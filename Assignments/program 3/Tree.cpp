#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(){
    //initialize pointer
    root = nullptr;
}

Tree::~Tree(){
    destructorHelper(root);
}
//helper function to destruct tree
void Tree::destructorHelper(Node *curr)const{
    if(curr==nullptr){ 
        return;
    }
    destructorHelper(curr->left); //call function to all children nodes
    destructorHelper(curr->middle);
    destructorHelper(curr->right);

    delete curr;
}

void Tree::preOrder() const {
    preOrder(root);
}


void Tree::preOrder(Node *curr) const {
    if(curr == nullptr) { //if tree is empty
        return;
        
    }
    else{
        if(curr->count == 1) {  //if there is one node, no duplicates
            cout << curr->small << ", "; //output node
            preOrder(curr->left); //and left and right nodes. 
            preOrder(curr->right);
        }
        else if(curr->count == 2) {  //if there is a duplicate
            cout << curr->small << ", "; //ooutput node, then left, then the right side of node, then the middle, then rifht 
            preOrder(curr->left);
            cout << curr->large << ", ";
            preOrder(curr->middle);
            preOrder(curr->right);
        }
    }
}

void Tree::inOrder() const{
    inOrder(root);
}


void Tree::inOrder(Node *curr) const { //helper function
    if(curr == nullptr) {
        return;
    }
    else {
        if(curr->count == 1){  //in order: left, me, right. check for duplicates first
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->right);
        }
        else if(curr->count == 2){  //follow same process just changing the order.
            inOrder(curr->left);
            cout << curr->small << ", ";
            inOrder(curr->middle);
            cout << curr->large << ", ";
            inOrder(curr->right);
        }
    }
}


void Tree::postOrder() const {
    postOrder(root);
}
void Tree::postOrder(Node *curr) const { //helper function 
    if(curr == nullptr){
        return;
    }
    else{
        if(curr->count == 1) { 
            postOrder(curr->left);
            postOrder(curr->right);
            cout << curr->small << ", ";
        }
        else if(curr->count == 2) { 
            postOrder(curr->left);
            postOrder(curr->middle);
            cout << curr->small << ", ";
            postOrder(curr->right);
            cout << curr->large << ", ";
        }
    }
}


void Tree::split(Node* curr, const string &str) {
    Node *leftz = nullptr;  // initialize new pointers to null
    Node *rightz = nullptr;
    string middle = "";

    if(curr->large == ""){  //check if curr node is a leaf
        return;
    }
    if(str == curr->small || str == curr->large){ //check for duplicates
        throw runtime_error("duplicates");
    }
    
    //if the string is smaller than the small part of the node (checking position )
    if(str < curr->small){ 
        leftz = new Node(str);
        rightz = new Node(curr->large);
        middle = curr->small;

        
    }
    else if(str > curr->large){ //checking position of the string in order to find where to split node
        leftz = new Node(curr->small);
        middle = curr->large;
        rightz = new Node(str);


    }
    else{ 
        leftz = new Node(curr->small);
        middle = str;
        rightz = new Node(curr->large);

    }
// Clear the current node's large element and decrement count
    curr->large = "";
    --curr->count;

    if (curr->parent != nullptr) { // If the node has a parent (not root)
        curr->parent->large = middle; // Update the large element of the parent with the middle value
        ++curr->parent->count; // Increment the count of the parent (since it now has an additional element)
        curr->parent->middle = leftz; // Set the left child of the parent to the new left node
        leftz->parent = curr->parent; // Update the parent pointer of the left node
        curr->parent->right = rightz; // update right child of the parent to the new right node
        rightz->parent = curr->parent; // set up parent pointer of the right node
    }
    else { 
    // If the current node is the root (has no parent)

        curr->small = middle; // Update the small element of the current node with the middle value
        curr->left = leftz; // Set the left child of the current node to the new left node
        curr->right = rightz; // Set the right child of the current node to the new right node
        leftz->parent = curr; // Update the parent pointer of the left node
        rightz->parent = curr; // Update the parent pointer of the right node
    }

}

bool Tree::search(const string &str) const{
    //call helper function
    return searchHelper(str, root);
}

//question: does it matter the order you pass someone in a function? should it be the pointer first and then the string
bool Tree::searchHelper(const string &str, Node *curr)const {
    //first edge case: tree is empty
    if(curr==nullptr){
        return false;
    }
    if(curr->small==str|| curr->large==str){ //if it is one of the components of the node
        return true;
    }
    else{
        if(str<curr->small){
            return searchHelper(str, curr->left);
        }
        else if(curr->count==2 && str< curr->large){
            return searchHelper(str, curr->middle);
        }
        else{
            return searchHelper(str, curr->right);
        }
    }
}




void Tree::insert(const string &str){
    //insert for a B tree:
    /*
    we will need a helper function for this. just call helper function.
    can't return something in a void function.
    */
    if (root == nullptr) { //WAS GETTING ERRORS FOR FORGETTING TO CHECK IF TREE IS EMPTY ARGHHHHHGHHHH
        Node* newNode = new Node(str);
        root = newNode;
    } 
    else { //5 hours later...
        insertHelper(str, root);
    }
}

//pointer function that will return the inserted node in the tree.
void Tree::insertHelper(const string &str, Node* curr) {
    // First edge case: If the current node is nullptr (leaf node or uninitialized), return.
    if (curr == nullptr) { 
        return;
    }

    // If the string is less than the left side of the current node.
    if (str < curr->small) { 
        if (curr->count == 1) { 
            // If the current node has only one element, insert the string in the same node and increment count
            if (curr->left == nullptr) { 
                curr->large = curr->small; 
                curr->small = str;
                ++curr->count; 
            }
            else {
                insertHelper(str, curr->left);
            }
        }
        // If the node is full, we need to split it.
        else if (curr->count == 2) {  
            if (curr->left != nullptr) { 
                insertHelper(str, curr->left);
            }
            else { 
                split(curr, str);
            }
        }
        else { 
            split(curr, str); 
        }
    }
    // If the string is greater than the left side of the current node.
    else if (str > curr->small) { 
        if (curr->count == 1) { 
            // If the current node has only one element, insert the string accordingly.
            if (curr->right == nullptr) { 
                curr->large = str;
                ++curr->count;
            }
            else {
                insertHelper(str, curr->right); 
            }
        }
        else if (curr->count == 2 && str < curr->large) {
            // If the current node has two elements and the string is less than the large element.
            if (curr->middle != nullptr) { 
                insertHelper(str, curr->middle);
            }
            else { 
                split(curr, str);
            }
        } 
        else {
            split(curr, str); 
        }
    }
}

// Now the remove function
void Tree::remove(const string &str) {
    removeHelper(str, root);
}

// Helper function for removing a node with a given string
void Tree::removeHelper(const string &str, Node* curr) {
    if (curr == nullptr) {
        return; // Base case: If the current node is nullptr, return.
    }

    // If the string is found in the tree, proceed with removal.
    if (searchHelper(str, curr)) {
        curr = searchNode(str, curr); 

        if (curr->parent == nullptr) { // Node is a leaf
            if (curr->left == nullptr && curr->right == nullptr) { // No children
                if (curr->count == 1) { //  only one element
                    delete curr;
                    root = nullptr;
                }
                else {
                    // If there are two elements, remove the right one.
                    if (curr->small == str) {
                        curr->small = curr->large;
                        curr->large = "";
                        --curr->count;
                    }
                    else if (curr->large == str) {
                        curr->large = "";
                        --curr->count;
                    }
                }
            }
            else { // Not a leaf
                // Update the current node with values from its children.
                curr->small = curr->left->small;
                curr->large = curr->right->small;
                ++curr->count;
                delete curr->right;
                delete curr->left;
                curr->right = nullptr;
                curr->left = nullptr;
            }
        }
        else { // Internal node in the tree
            if (curr->count == 1) { 
                // If the current node has one element, update parent.
                Node *mother = curr->parent; //create mother node, which is parent of curr node
                if (mother->right == curr) { 
                    mother->large = mother->small;
                    mother->small = mother->left->small;
                }
                else if (mother->left == curr) { 
                    mother->large = mother->right->small;
                }
                ++mother->count;
                delete mother->left;
                delete mother->right;
                mother->left = nullptr;
                mother->right = nullptr;
            }
            else { 
                // If the current node has two elements, handle removal by updating the current node.
                if (curr->small == str) { 
                    curr->small = curr->large;
                }
                --curr->count;
                curr->large = "";         
            }
        }
    }
}

// Helper function to search for a node with a given key
Node* Tree::searchNode(const string &key, Node* curr) {
    if (curr == nullptr) { 
        return nullptr; // If empty, return nullptr.
    }
    if (curr->small == key || curr->large == key) { 
        return curr; // If the key is found, return the current node.
    }
    else {
        // Recursively search in the appropriate subtree.
        if (key < curr->small) {
            return searchNode(key, curr->left);
        }
        else if (curr->count == 2 && key < curr->large) {
            return searchNode(key, curr->middle); 
        }
        else {
            return searchNode(key, curr->right); 
        }
    }
}
