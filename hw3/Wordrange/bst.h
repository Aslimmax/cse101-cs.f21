/**
 * Filename: bst.h
 * 
 * Header file for the class BST that represents a binary
 * search tree
 * 
 * C. Seshadhri, Jan 2020
 * A. Lim, Nov 2021
 */

#ifndef BST_H
#define BST_H

#include <string>
#include <vector>

using namespace std;

// node struct to hold data
class Node {
	public:
		string key;
//         int height; // AVL property
//         int subtreeSize; // Number of descendants a node has
		Node *left, *right, *parent;
	
		Node() { // default constructor
			left = right = parent = NULL; // Setting everything to NULL
//             height = 1; // Height of a leaf node is 1
//             subtreeSize = 0; // A leaf Node has 0 descendents
		}
	
		Node(string val) { // Constructor that sets key to val
			key = val;
			left = right = parent = NULL; // Setting everything to NULL
//             height = 1; // Height of a leaf node is 1
//             subtreeSize = 0; // A leaf Node has 0 descendents
		}
    
        // Helper functions
//         void setHeight(int height_) { height = height_; }
//         void setSubtreeSize(int size) { subtreeSize = size; }
//         int getHeight() const { return height; }
//         int getSubtreeSize() const { return subtreeSize; }
};

class BST {
	private:
		Node *root; // stores root of tree
	public:
		BST(); // default constructor sets root to NULL
	
		void insert (string); // insert int into list
		void insert(Node*, Node*); // recursive version that inserts a node
		// find int in tree and return pointer to node with int. If there
		// are multiple copies, this only finds one copy
		Node* find(string);
		Node* find(Node*, string); // recursive version that finds in a rooted subtree
		Node* minNode(Node*); // gets minimum node in a rooter subtree
		Node* maxNode(Node*); // gets maximum node in a rooted subtree
		// remove a node with int (if it exists), and return pointer to
		// deleted node. This does not delete all nodes with the value.
		Node* deleteKey(string); 
		// try to delete node pointed by argument. This also returns the
		// node, isolated from the tree
		Node* deleteNode(Node*);
		// deletes every node to prevent memory leaks, and frees memory
		void deleteBST();
		// deletes every Node in subtree rooted at start to prevent memory
		// leaks
		void deleteBST(Node* start);
		string printInOrder(); // Construct string wtih tree printed InOrder
		// Construct string with rooted subtree printed InOrder
		string printInOrder(Node* start);
		string printPreOrder(); // Construct string with tree printed PreOrder
		// Construct string with rooted subtree printed PreOrder
		string printPreOrder(Node* start);
		string printPostOrder(); // Construct string with tree printed PostOrder
		// Construct string with rooted subtree printed PostOrder
		string printPostOrder(Node* start);
        // Determine the number of elements between val1 and val2 rooted at start
        int numItemsInRange(string val1, string val2);
        // Determine the number of elements between val1 and val2 lexicographically.
        // This is the recursive implementation.
        void numItemsInRange(Node* start, string val1, string val2, int&);
        // Print out a visualization of the tree. This is the driver function.
        void printTree();
        // Print out a visualization of the tree. This is the recursive version.
        void printTree(string prefix, Node* start, bool isLeft);
    
        // AVL Functions
        // Recurse up the tree and update the height and subtree size of each Node 
        // along the rooted Node's ancestors
//         void updateHeights(Node* start, bool modified);
        // Recurse up the tree and determine if each subtree satisfies the AVL invariant
        // that is the different in height of the left and right subtree is {-1, 0, 1}
//         void balanceTree(Node* start);
        // Rotation functions
//         void rotateLeft(Node* start);
//         void rotateRight(Node* start);
//         void rotateRightLeft(Node* start);
//         void rotateLeftRight(Node* start);
        // Calculate the balance factor between the start->left and start->right node
//         int calculateBalanceFactor(Node* start);
};

#endif