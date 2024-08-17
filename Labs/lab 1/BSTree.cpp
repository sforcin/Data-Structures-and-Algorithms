#include <iostream>
#include "BSTree.h"
#include <string>
#include "Node.h"

using namespace std;

// BSTree::~BSTree(){
//     // while(root){
//     //     remove (root->str);
//     // }
//     delete root;
// }

void BSTree::destructorHelper(Node* node){
    if (node){
        destructorHelper(node->left);
        destructorHelper(node->right);
        delete node;
    }
}

BSTree::~BSTree(){
    destructorHelper(root);
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
    if(curr != 0) {
        if(key == curr->str) {
            return curr;
        }
        else {
            if(key < curr->str) {
                return search(key, curr->left);
            }
            else {
                return search(key, curr->right);
            }
        }
    }
    else {
        return 0;
    }
}


//NOW I WILL DO A INSERT 
//in order to insert something, we need to find where to insert it first.
// if the bst is empty, we just add new string to the root

void BSTree::insert(const string &key){

    Node *curr = root; // create a new pointer that points to the root of the tree
    // check if node is already on the tree

    if(search(key)){
        curr = search(key, root);
        curr->count = curr->count +1;
    }

    else{
        // if it is not yet in the tree, we will need to add something there, so we create a new node 
        Node* newNode = new Node(key);
        if(root == nullptr){
           root  = newNode;
        }
        else{
            while(1){
                if(key<curr->str){
                    if(curr->left == 0){
                        curr->left = newNode;
                        return; //operation insert is completed.
                    }
                    else{
                        curr = curr->left;
                    }
                }
                else if(curr->right ==0){
                        curr->right = newNode;
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
string BSTree::largest() const{
    Node* curr = root;
    if(curr == 0){
        return "";
    }

 //   Node *curr = root;

    while(curr->right!=0){
        curr = curr->right;
    }
    return curr->str;
}

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

    if(!search(key)){
        return -1;
    }

    Node *curr = search(key, root);
    Node *leftNode = curr;
    Node *rightNode = curr;
    int countR= 0;
    int countL=0;

    if(curr->left !=0){
        leftNode = leftNode->left;
        countL ++;
        countL = countL +height(leftNode->str);
    }
    if(curr->right !=0){
        rightNode = rightNode->right;
        countR++;
        countR = countR + height(rightNode->str);
    }
    if(countL >= countR){
        return countL;
    }
    else {
        return countR;
    }

}


void BSTree::remove( const string& key){
    removeHelper(root, key);
}

Node* BSTree::removeHelper(Node* curr, const string &key) {
    if (curr == nullptr) {
        return nullptr;
    }

    if (key < curr->str) { // Go left
        curr->left = removeHelper(curr->left, key);
    } else if (key > curr->str) { // Go right
        curr->right = removeHelper(curr->right, key);
    } else { // Node found!
        if (curr->count > 1) {
            curr->count = curr->count - 1; // Decrement the counter if > 1
        } else { // Counter becomes 0; begin shifting process
            // No children
            if (curr->left == nullptr && curr->right == nullptr) {
                delete curr;
                return nullptr;
            } else if (curr->left != nullptr) { // A left child exists
                Node* victim = removeLeft(curr);
                string victim_str = victim->str;
                int victim_int = victim->count;

                victim->count = 1;
                removeHelper(curr, victim->str); // Remove the victim now

                // Copy over data from victim
                curr->str = victim_str;
                curr->count = victim_int;
            } else { // Only right child
                Node* victim = removeRight(curr);
                string victim_str = victim->str;
                int victim_int = victim->count;

                victim->count = 1;
                removeHelper(curr, victim->str); // Remove the victim now

                // Copy over data from victim
                curr->str = victim_str;
                curr->count = victim_int;
            }
        }
    }

    return curr;
}

Node* BSTree::removeLeft(Node *curr){
    Node *temp = curr;
    temp = temp->left;
    while(temp->right!=nullptr){
        temp = temp->right;
    }
    return temp;
}
Node* BSTree::removeRight(Node *curr){
    Node *temp = curr;
    temp = temp->right;
    while(temp->left!=nullptr){
        temp=temp->left;
    }
    return temp;
}


void BSTree::inOrder(Node *curr) const {
    if(curr!=0){
        inOrder(curr->left);
        cout<< curr->str<< '('<< curr->count<< "), ";
        inOrder(curr->right);
    }
}

void BSTree::postOrder(Node *curr) const{
    if(curr !=0){
        postOrder(curr->left);
        postOrder(curr->right);
        cout<< curr->str<< '('<< curr->count <<"), ";
    }
}

void BSTree::preOrder(Node *curr) const {
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

