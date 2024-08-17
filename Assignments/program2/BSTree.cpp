#include <iostream>
#include "BSTree.h"
#include <string>
#include "Node.h"

using namespace std;

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






        /* Remove a specified string from the tree. 
           Be sure to maintain all bianry search tree properties. 
           If removing a node with a count greater than 1, just decrement the count, otherwise, 
           if the count is simply 1, remove the node. 
            You MUST follow the remove algorithm shown in the slides and discussed in class or else 
            your program will not pass the test functions. 
            When removing, 
                if removing a leaf node, simply remove the leaf. Otherwise, 
                if the node to remove has a left child, replace the node to remove with the largest 
                string value that is smaller than the current string to remove 
                (i.e. find the largest value in the left subtree of the node to remove). 
                If the node has no left child, replace the node to remove with the smallest value 
                larger than the current string to remove 
                (i.e. find the smallest value in the right subtree of the node to remove. 
         */



// void BSTree::remove(const string &key){
//     removeHelper(root, key);
// }
// //we need a helper function, because this only passes in a key, and we need a function that passes in a key 
// //and a current node to access other nodes of the tree

// void BSTree::removeHelper(Node*& curr, const string& key) {
//     if (curr==nullptr) {
//         return;
//     }

//     if (key < curr->str) {
//         removeHelper(curr->left, key);
//     } else if (key > curr->str) {
//         removeHelper(curr->right, key);
//     } else {
//         if (curr->count > 1) {
//             // Decrement count for duplicate string
//             curr->count--;
//         } else {
//             if (!curr->left && !curr->right) {
//                 // Case 1: Node is a leaf
//                 delete curr;
//                 curr = nullptr;
//             } else if (!curr->left) {
//                 // Case 2: Node has only a right child
//                 Node* temp = curr;
//                 curr = curr->right;
//                 delete temp;
//             } else if (!curr->right) {
//                 // Case 2: Node has only a left child
//                 Node* temp = curr;
//                 curr = curr->left;
//                 delete temp;
//             } else {
//                 // Case 3: Node has both left and right children

//                 // Find and remove the leftmost node in the right subtree
//                 Node* minRightParent = curr;
//                 Node* minRight = curr->right;

//                 while (minRight->left != nullptr) {
//                     minRightParent = minRight;
//                     minRight = minRight->left;
//                 }

//                 // Replace the data of the current node with the data of the leftmost node
//                 curr->str = minRight->str;
//                 curr->count = minRight->count;

//                 // Remove the leftmost node (smallest node) from the right subtree
//                 if (minRightParent == curr) {
//                     minRightParent->right = minRight->right;
//                 } else {
//                     minRightParent->left = minRight->right;
//                 }

//                 delete minRight;
//             }
//         }
//     }
// }


// void BSTree::remove(Node *key) {
// 	Node *curr = key;
// 	Node *succ = 0;

// 	if(curr->left == 0 && curr->right == 0) {
// 		if(curr->parent != 0) {
// 			if(curr->parent->left == curr) {
// 				curr->parent->left = 0;
// 			}
// 			else {
// 				curr->parent->right = 0;
// 			}
// 		}
// 		else {
// 			root = 0;
// 		}
// 		delete curr;
// 	}
// 	else if(curr->left != 0) {
// 		succ = curr->left;
// 		while(succ->right != 0) {
// 			succ = succ->right;
// 		}
// 		*curr = *succ;
// 		remove(succ);
// 	}
// 	else {
// 		succ = curr->right;
// 		while(succ->left != 0) {
// 			succ = succ->left;
// 		}
// 		*curr = *succ;
// 		remove(succ);
// 	}
// }

// void BSTree::remove(const string &key) {
//     if(search(key)) {
//         Node *curr = search(key, root);
        
//         if(curr->count > 1) {
//             curr->count = curr->count - 1;
//         }
//         else {
//             remove(curr);
//         }
//     }
// }


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



void BSTree::remove(const string &key){
    root = removeHelper(root,key);
}

Node* BSTree::removeHelper(Node* curr, const string& key) {
    Node* victim = nullptr;

    if (curr == nullptr) {
        return nullptr;
    }

    if (key < curr->str) {
        curr->left = removeHelper(curr->left, key);
        return curr;
    } else if (key > curr->str) {
        curr->right = removeHelper(curr->right, key);
        return curr;
    }

    curr->count--;

    if (curr->count > 0) {
        return curr;
    }

    if (curr->left == nullptr && curr->right == nullptr) {
        delete curr;
        return nullptr;
    } else if (curr->left != nullptr) {
        victim = curr->left;
        while (victim->right != nullptr) {
            victim = victim->right;
        }
        curr->str = victim->str;
        curr->count = victim->count;
        victim->count = 1;
        curr->left = removeHelper(curr->left, victim->str);
        return curr;
    }

    // Add this return statement
    return curr;
}
