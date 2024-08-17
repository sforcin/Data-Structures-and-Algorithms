#include <iostream>
#include "BSTree.h"
#include <string>
#include "Node.h"

using namespace std;

//create a destructor since we created new ndoes
BSTree::~BSTree(){
    // while(root){
    //     remove (root->str);
    // }
    delete root;
}

BSTree::BSTree(){
    root =0;
}

//the search function only takes in one parameter, so I am going to implement a helper function thhat takes in
// 2 parameters, so I can access the left and right subtree of each node in the bst.

//SEARCH DONE
bool BSTree::search(const string&key) const{
    return search(key, root);
}

Node* BSTree::search(const string &key, Node* curr) const {
    if(curr != 0) { //if tree is not empty
        if(key == curr->str) {
            return curr; //if we have found the key, return the curr node where ir has been found.
        }
        else {
            if(key < curr->str) { //if key is less, go to the left subtree
                return search(key, curr->left);
            }
            else { //go to the right subtree. 
                return search(key, curr->right);
            }
        }
    }
    else { //key is not found.
        return 0;
    }
}


//NOW I WILL DO A INSERT 
//in order to insert something, we need to find where to insert it first.
// if the bst is empty, we just add new string to the root

void BSTree::insert(const string &key){

    Node *curr = root; // create a new pointer that points to the root of the tree
    // check if node is already on the tree

    if(search(key)){ //we search if the key is already in the tree, if it is
        curr = search(key, root);
        curr->count = curr->count +1; //you just increment the count of it
    }

    else{
        // if it is not yet in the tree, we will need to add something there, so we create a new node 
        Node* newNode = new Node(key); 
        if(root == nullptr){ //if tree is empty, add it to the root
           root  = newNode;
        }
        else{
            while(1){
                if(key<curr->str){ //if the new we are adding is less than the current node, go to left subtree 
                    if(curr->left == 0){ //if the left subtree is emoty
                        curr->left = newNode; // add new node there
                        return; //operation insert is completed.
                    }
                    else{
                        curr = curr->left; //if not, send the curr to the left subtree
                    }
                }
                else if(curr->right ==0){ //if right subtree is empty
                        curr->right = newNode; // add new node there
                        newNode->parent = curr; 
                        return;
                    
                }
                else{
                    curr = curr->right;
                }

            }
        }
    }

    
}

//Find and return largest value in the tree. return empty string if the tree is empty
//the largest node in the tree is the rightmost node
string BSTree::largest() const{
    Node* curr = root;
    if(curr == 0){ //start at root, check if tree is empty
        return "";
    }

 //   Node *curr = root;

    while(curr->right!=0){ //while the right child is not null 
        curr = curr->right; // keep traversing right
    }
    return curr->str;
}


//the smallest node in the tree is the leftmost node, so keep traversing there anf then return it.
string BSTree::smallest() const{
    Node *curr = root;   
    if(curr == 0){
        return "";
    }


    while(curr->left!=0){
        curr = curr->left;
    }
    return curr->str;
}

/* To find height of the tree: 
    Will need to find the "longest way" down, keeping track of the levels.
    In order to do that, i think I am going to access each sub tree and find the lowest node (leaf,)
    which is when the node has no children.
    while doing that, i am going to create an integer called count to keep track of the levels
    Then I am going to compare the count for each subtree,
    and return the count, which will be the total length

    i actually may need two counts, countA and countB. one for each sub tree... idk yet

    wait. it wants the height of the node we are using. so we need to create a node and then point it to the root 
    of the tree. then we can start transversing down the tree to find the height at that node. 
    in this case, we just have to go down until we find the node, then we stop there. i think that is easier

    just do a helper function. its easier 
*/

int BSTree::height(const string &key) const{

    if(!search(key)){ //if the node is not in the tree, lets not waste memory and time and exit the function
        return -1;
    }

    Node *curr = search(key, root); //make the curr poointer point to the location of the node you want to know the heigth of
    Node *leftNode = curr;
    Node *rightNode = curr;
    int countR= 0;
    int countL=0;

    if(curr->left !=0){ //if left subtree is not empty, keep traversing left until it is a leaf node.
        leftNode = leftNode->left;
        countL ++;
        countL = countL +height(leftNode->str); //keep track of the count
    }
    if(curr->right !=0){ //do the same thing for the right subtree
        rightNode = rightNode->right;
        countR++; //increment the count
        countR = countR + height(rightNode->str); //keep track of the count
    }
    if(countL >= countR){
        return countL;
    }
    else {
        return countR; //return largest value
    }

}

//helper function
void BSTree::inOrder(Node *curr) const {
    //in order is left, me, right
    if(curr!=0){ //regular function called at root, so if the tree is not empty
        inOrder(curr->left);// call the inOrder in the left subtree
        cout<< curr->str<< '('<< curr->count<< "), "; //output the content of the left child and its count
        inOrder(curr->right); //repear process to right subtree
    }
}

void BSTree::postOrder(Node *curr) const{
    //post order is left, right, me
    if(curr !=0){
        postOrder(curr->left);
        postOrder(curr->right);
        cout<< curr->str<< '('<< curr->count <<"), ";
    }
}

void BSTree::preOrder(Node *curr) const {
    //pre order is me, left, right
	if(curr != 0) {
		cout << curr->str << '(' << curr->count << "), ";
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void BSTree::preOrder() const{
    preOrder(root);
    cout <<endl;
}

void BSTree::inOrder() const{
    inOrder(root);
    cout << endl;
}


void BSTree::postOrder() const{
    postOrder(root);
    cout << endl;
}


//original function, basically only used to call helper function
void BSTree::remove(const string &key){
    root = removeHelper(root,key);
}

Node* BSTree::removeHelper(Node* curr, const string& key) {
    Node* victim = nullptr; //

    if (curr == nullptr) { //if tree is empty, return null (pointer function).
        return nullptr;
    }

    if (key < curr->str) { //if the key is less than the curr, go to left subtree and call helper function
        curr->left = removeHelper(curr->left, key);
        return curr; //add return statements to every case. i was losing 10 points because of this
    } else if (key > curr->str) { //if the key we want is greater than the current key
        curr->right = removeHelper(curr->right, key); //go to the right subtree and call helper function
        return curr;
    }

    curr->count--; //decrease count

    if (curr->count > 0) { // if the count is more than one, means there is a duplicate
        return curr;
    }

    if (curr->left == nullptr && curr->right == nullptr) {
        delete curr; //if tree has no children
        return nullptr; //just delete the leaf and return null
    } 
    else if (curr->left != nullptr) { //if there is a left side
        victim = curr->left; //set the victim to the left child
        while (victim->right != nullptr) { //until you reach the rightmost child of ur left subtree
            victim = victim->right; //keep going to the right
        }
        curr->str = victim->str; //
        curr->count = victim->count;
        victim->count = 1; //count is only one, no duplicates
        curr->left = removeHelper(curr->left, victim->str); //call helper function
        return curr;
    }
    else if(curr->right != nullptr){ //repeat the same process, if there is a right subtree as well. 
        victim = curr->right;
        while(victim->left != nullptr){
            victim = victim->left;
        }
        curr->str = victim->str;
        curr->count = victim->count;
        victim->count=1;
        curr->right = removeHelper(curr->right, victim->str);
        return curr;
    }


    // Add this return statement
    return curr;
}
