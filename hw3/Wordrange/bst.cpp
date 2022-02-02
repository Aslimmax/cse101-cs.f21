/**
 * Filename: bst.cpp
 * 
 * Contains the class BST that represents a binary search tree. This contains
 * some basic operations, such as insert, delete, find, and printing in
 * various traversal orders.
 * 
 * C. Seshadhri, Jan 2020
 * A. Lim, Nov 2021
 */

#include "bst.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

// Default constructor sets head and tail to NULL
BST::BST() {
	root = NULL;
}

/**
 * insert(int val)
 * Inserts the int val into tree, at the head of the list. Note there
 * may be multiple copies of val in the list. Just calls the recursive
 * function.
 * Input: int to insert into the BST
 * Output: void, just inserts new node
 */
void BST::insert(string val) {
	Node *to_insert = new Node(val); // Create a new Node with the value val
	if (root == NULL) // Tree is currently empty
		root = to_insert; // Make new Node the root
	else {
		insert(root, to_insert); // Make call to recurisve insert, starting from root
        // Update the heights of the ancestor's of the newly inserted node
//         updateHeights(to_insert, true);
//         printTree();
        // Recurse through tree and ensure that AVL invariant is maintained in every Node
//         balanceTree(to_insert);
    }
}

/**
 * insert(Node* start, Node* to_insert)
 * Inserts the Node to_insert into tree rooted at start. We will always call
 * with start being non-null. Note that there may be multiple copies of val
 * in the list.
 * Input: int to insert into the subtree
 * Output: void, just inserts new Node
 */
void BST::insert(Node* start, Node* to_insert) {
	// In general, this should not happen. We never call insert from a
	// NULL tree
	if (start == NULL)
			return;
	if (to_insert->key <= start->key) {
		// inserted node has smaller (or equal) key, so go left
		if (start->left == NULL) {
			start->left = to_insert; // make this Node the left child
			to_insert->parent = start; // set the parent pointer
			return;
		} else { // need to make recurisve call
			insert(start->left, to_insert);
			return;
		}
	} else { // inserted Node has larger key, so go right
		if (start->right == NULL) {
			start->right = to_insert; // make this Node the right child
			to_insert->parent = start; // set the parent pointer
			return;
		} else { // need to make recurisve call
			insert(start->right, to_insert);
			return;
		}
	}
}

/**
 * find(int val)
 * Finds a Node with key "val"
 * Input: int to be found
 * Output: a pointer to a Node containing val, if it exists. Otherwise,
 * it return null.
 * Technically, it finds the first Node with val, as it traverses down
 * the tree
 */
Node* BST::find(string val) {
	// Call the recursive function starting at root
	return find(root, val);
}

/**
 * find(Node* start, int val): Recursively tries to find a Node with
 * key "val", in subtree rooted at val
 * Input: int to be found
 * Output: a pointer to a Node containing val, if it exists. Otherwise,
 * it returns NULL
 * Technically, it finds the first Node with val, as it traverses down
 * the tree
 */
Node* BST::find(Node* start, string val) {
	// Tree is empty or we found val
	if (start == NULL || start->key == val)
		return start;
	if (val < start->key) // val is smaller, so go left
		return find(start->left, val);
	else // val is larger, so go right
		return find(start->right, val);
}

/**
 * minNode(Node* start)
 * Gets the minimum Node in subtree rooted at start
 * Input: pointer to subtree root
 * Output: pointer to the minimum Node in the subtree
 */
Node* BST::minNode(Node* start) {
	// Typically, this should not happen. But let's return the safe thing
	if (start == NULL)
		return NULL;
	// Base case: we have found the minimum
	if (start->left == NULL)
		return start;
	else
		return minNode(start->left); // recursive call in left subtree
}

/**
 * maxNode(Node* start)
 * Gets the maximum Node in subtree rooted at start
 * Input: pointer to subtree root
 * Output: pointer to the maximum Node in the subtree
 */
Node* BST::maxNode(Node* start) {
    // Typically, this should not happen. But let's return the safe thing
    if (start == NULL)
        return NULL;
    // Base case: we have found the maximum
    if (start->right == NULL)
        return start;
    else
        return maxNode(start->right); // recurisve call in right subtree
}

/**
 * deleteNode(Node* to_delete)
 * Delete the input node, and return pointer to the deleted. The node
 * will be isolated from the tree, to prevent memory leaks.
 * Input: Node to be removed
 * Output: pointer to Node that was deleted. If no Node is deleted,
 * return NULL.
 */
Node* BST::deleteNode(Node* to_delete) {
    // val not present in tree, so return NULL
    if(to_delete == NULL)
        return NULL;
    
    // determine if node to delete is root
    bool isRoot = (to_delete == root) ? true : false;
    bool isLeftChild = false;
    if (!isRoot) // if this is not the root
        // determine if Node is left child of parent. Note that line throws error
        // iff to_delete is root
        isLeftChild = (to_delete->parent->left == to_delete) ? true : false;
    
    bool isDeleted = false; // convenient flag for writing code
    
    // if to_delete's left child is NULL, then we can splice this node off. We set
    // the appropriate pointer of the parent to the right child of to_delete
    if (to_delete->left == NULL) {
        // cout << "left is null, isLeftChild is " + to_string(isLeftChild) << endl;
        // cout << "parent is " + to_string(to_delete->parent->key) << endl;
        if (isRoot) {// if deleting root, then we reset root
            root = to_delete->right;
            if (root != NULL)
                root->parent = NULL; // set parent to be NULL
        } else {
            if (isLeftChild) // Node is left child of parent
                // setting left child of parent to be right child of Node
                to_delete->parent->left = to_delete->right;
            else // Node is right child of parent
                // setting right child of parent to be right child of Node
                to_delete->parent->right = to_delete->right;
            if (to_delete->right != NULL) // to_delete is not a leaf
                // update parent of the child of the deleted Node, to be parent
                // of deleted Node
                to_delete->right->parent = to_delete->parent;
        }
        isDeleted = true; // delete is done
    }
    // Suppose Node is not deleted yet, and it's right child is NULL. We splice off
    // as before, by setting parent's child pointer to to_delete->left
    if (!isDeleted && to_delete->right == NULL) {
        if (isRoot) { // if deleted root, then we reset root
            root = to_delete->left;
            if (root != NULL)
                root->parent = NULL; // set parent to be NULL
        } else {
            if (isLeftChild) // Node is left child of parent
                // setting left child of parent to be left child of Node
                to_delete->parent->left = to_delete->left;
            else // node is right child of parent
                // setting right child of parent to be left child of Node
                to_delete->parent->right = to_delete->left;
            if (to_delete->left != NULL) // to delete is not a leaf
                // update parent of the child of deleted Node, to be parent
                // of deleted NOde
                to_delete->left->parent = to_delete->parent;
        }
        isDeleted = true; // delete is done
    }
    if (isDeleted) { // so node has been deleted
        to_delete->left = to_delete->right = NULL;
        return to_delete;
    }
    
    // The splicing case is done, so now for for the recursive case. Both children
    // of to_delete are not null, so we replace the data in to_delete by the
    // successor. Then we delete the successor Node
    // first, get the minimum Node of the right subtree
    Node* succ = minNode(to_delete->right);
    to_delete->key = succ->key;
    // cout << "Replacing with " + to_string(succ->key) << endl;
    // Make recursive call on succ. Note that succ has one null child, so this
    // recursive call will terminate without any other recursive calls
    return deleteNode(succ);
}

/**
 * deleteBST()
 * Deletes every Node to prevent memory leaks.
 * Input: none
 * Output: void, just deletes every Node of the list
 */
void BST::deleteBST() {
    deleteBST(root);
}

/**
 * deleteBST(Node* start)
 * Deletes every Node in subtree rooted at start to prevent memory leaks.
 * Input: Node* start
 * Output: void, just deletes every Node of the list
 */
void BST::deleteBST(Node* start) {
    if(start == NULL) // tree is already empty
        return;
    deleteBST(start->left); // delete left subtree
    deleteBST(start->right); // delete right subtree
    delete(start); // delete node itself
}

/**
 * printInOrder()
 * Prints tree in order. Calls the recursive function from the root
 * Input: none
 * Output: string that has all elements of the tree in order
 */
string BST::printInOrder() {
    return printInOrder(root);
}

/**
 * printPreOrder()
 * Prints tree Preorder. Calls the recursive function from the root
 * Input: none
 * Output: string that has all element of the tree pre order
 */
string BST::printPreOrder() {
    return printPreOrder(root);
}

/**
 * printPostOrder()
 * Prints tree Postorder. Calls the recursive function from the root
 * Input: none
 * Output: string that has all element of the tree post order
 */
string BST::printPostOrder() {
    return printPostOrder(root);
}

/**
 * printInOrder(Node* start)
 * Prints rooted subtree tree in order, by making recursive calls
 * Input: Node* start
 * Output: string that has all elements of the rooted tree in order
 */
string BST::printInOrder(Node* start) {
    if (start == NULL) // base case
        return ""; // return empty string
    string leftpart = printInOrder(start->left);
    string rightpart = printInOrder(start->right);
    string output = start->key;
    if (leftpart.length() != 0) // left part is empty
        output = leftpart + " " + output; // append left part
    if (rightpart.length() != 0) // right part is empty
        output = output + " " + rightpart; // append right part
    return output;
}

/**
 * printPreOrder(Node* start)
 * Prints rooted subtree tree preorder, by making recursive calls
 * Input: Node* start
 * Output: string that has all elements of the rooted tree in post order
 */
string BST::printPreOrder(Node* start) {
    if (start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPreOrder(start->left);
    string rightpart = printPreOrder(start->right);
    string output = start->key;
    if(leftpart.length() != 0) // left part is empty
        output = output + " " + leftpart; // append left part
    if(rightpart.length() != 0) // right part is empty
        output = output + " " + rightpart; // append right part
    return output;
}

/**
 * printPostOrder(Node* start)
 * Prints rooted subtree tree postorder, by making recursive calls
 * Input: Node* start
 * Output: string that has all elements of the rooted tree in post order
 */
string BST::printPostOrder(Node* start) {
    if (start == NULL) // base case
        return ""; // return empty string
    string leftpart = printPostOrder(start->left);
    string rightpart = printPostOrder(start->right);
    string output = start->key;
    if (rightpart.length() != 0) // right part is empty
        output = rightpart + " " + output; // append left part
    if (leftpart.length() != 0) // left part is empty
        output + leftpart + " " + output; // append right part
    return output;
}

/**
 * printTree()
 * Print out a visualization of the tree.
 * Input: none
 * Output: none
 */
void BST::printTree() {
    printTree("", root, false);
}

/**
 * printTree(string prefix, Node* start, bool isLeft)
 * Print out a visualization of the tree. This is the recursive version.
 * |-- is left child of Node, \-- is right child of Node
 * Input: string prefix, Node* start, bool isLeft
 * Output: none
 */
void BST::printTree(string prefix, Node* start, bool isLeft) {
    if (start != NULL) {
        // Determine proper indent identifier
        string indent = (isLeft) ? "|--" : "\\--";
        // Output string
        cout << prefix << indent << start->key << endl;
        // Determine next output indentation
        indent = (isLeft) ? "|   " : "    ";
        prefix += indent;
        
        // Recurse through left and right children
        printTree(prefix, start->left, true);
        printTree(prefix, start->right, false);
    }
}

/**
 * numItemsInRange()
 * Determine the number of elements between val1 and val2 rooted at start
 * Input: string val1, val2 
 * Output: number of elements between val1 and val2
 */
int BST::numItemsInRange(string val1, string val2) {
    // Initialize count to store the number of elements that are between
    // val1 and val2
    int count = 0;
    // Validate that the BST is not empty. If it is, return initial value of
    // count (0)
    if (root != NULL) {
        numItemsInRange(root, val1, val2, count);
    }
    return count;
}

/**
 * numItemsInRange(Node* start, int& count)
 * Determine the number of elements between val1 and val2 lexicographically.
 * This is the recursive implementation.
 * Input: Node* start, int count reference
 * Output: none, but int count is modified
 */
void BST::numItemsInRange(Node* start, string val1, string val2, int& count) {
    if (start == NULL) // Base case
        return;
    
    // Recurse through left child
    numItemsInRange(start->left, val1, val2, count);
    // Recurse through right child
    numItemsInRange(start->right, val1, val2, count);
    // Get the element in the current Node and check if it is between val1 and val2
    string output = start->key;
    if (output >= val1 && output <= val2) {
        count++;
    }
}

/**
 * updateHeights(Node* start)
 * Recurse up the tree and update the height and subtree size of each Node along the
 * rooted Node's ancestors. Will only modify the parent height if the start node's 
 * height was modified.
 * Input: Node* start (should be a newly inserted Node), bool modified
 * Output: none
 */ 
// void BST::updateHeights(Node* start, bool modified) {
//     // Base case: have reached the root of the BST
//     if (start == root)
//         return;

//     // Initialize references to the left and right child of start's parent
//     Node* leftChild = start->parent->left;
//     Node* rightChild = start->parent->right;
    
//     // Check if start needs to be modified (first recurse only) or if start
//     // has been modified in the previous recursion (every other recursion)
//     if (modified) {
//         // Get the heights of the start parent's left and right child
//         int leftChildHeight = (leftChild == NULL) ? 0 : leftChild->getHeight();
//         int rightChildHeight = (rightChild == NULL) ? 0 : rightChild->getHeight();
//         int parentHeight = start->parent->getHeight();
        
//         // Determine if start's height is greater than min of parent's left and 
//         // right child
//         if (start->getHeight() > min(leftChildHeight, rightChildHeight)) {
//             // Increment start parent's height by 1
//             start->parent->setHeight(parentHeight + 1);
//         } else {
//             modified = false;
//         }
//     }
    
//     // Get the subtree sizes of the start parent's left and right child.
//     // Initialized to 0 to represent a NULL child
//     int leftChildSubtreeSize = 0;
//     int rightChildSubtreeSize = 0;
    
//     // Determine if left child is not NULL
//     if (leftChild != NULL) {
//         // Get the subtree size of the left child
//         leftChildSubtreeSize = leftChild->getSubtreeSize();
//         // If the left child's subtree size = 0, then set left's size to 1
//         // properly calcualte the subtree size of start's parent. Need to include
//         // the child node in the calculation.
//         if (leftChildSubtreeSize == 0) {
//             leftChildSubtreeSize = 1;
//         } else {
//             leftChildSubtreeSize += 1;
//         }
//     }
    
//     // Determine if right child is not NULL
//     if (rightChild != NULL) {
//         // Get the subtree size of the right child
//         rightChildSubtreeSize = rightChild->getSubtreeSize();
//         // If the right child's subtree size = 0, then set right size to 1
//         // to properly calculate the subtree size of start's parent. Need to include
//         // the child node in the calculation.
//         if (rightChildSubtreeSize == 0) {
//             rightChildSubtreeSize = 1;
//         } else {
//             rightChildSubtreeSize += 1;
//         }
//     }
    
//     int newSubtreeSize = leftChildSubtreeSize + rightChildSubtreeSize;
//     // Update the parent's subtree size
//     start->parent->setSubtreeSize(newSubtreeSize);

//     // Continue recursing up the BST
//     updateHeights(start->parent, modified);
// }

/**
 * balanceTree(Node* start)
 * Recurse up the tree and update the height and subtree size of each Node
 * along the rooted Node's ancestors.
 * Input: Node* start
 * Output: none
 */
// void BST::balanceTree(Node* start) {
//     // Base case: have reached the root of the BST
//     if (start == NULL)
//         return;
    
// //     // Initialize references to the left and right child of start's parent
    
// //     // Get the height of the parent's children
    
// //     // Calculate the balance factor of the node

//     // Get the balanceFactor of start, start->right, and start->left
//     int startBalanceFactor = calculateBalanceFactor(start);
//     int leftBalanceFactor = 0;
//     int rightBalanceFactor = 0;
//     if (start->left != NULL) {
//         leftBalanceFactor = calculateBalanceFactor(start->left);
//     }
//     if (start->right != NULL) {
//         rightBalanceFactor = calculateBalanceFactor(start->right);
//     }
    
//     cout << "Current Node: " << start->key << " BF: " << startBalanceFactor << endl;
    
//     // Determine if the subtree rooted at start has a valid balanceFactor. If
//     // it doesn't perform the necessary operations
//     if (startBalanceFactor == 2) { // Right subtree is greater than left subtree
//         if (rightBalanceFactor >= 0) {
//             rotateLeft(start->right);
//         } else if (rightBalanceFactor == -1) {
//             rotateRight(start->right->left);
//             rotateLeft(start->right);
//         }
//     } 
//     else if (startBalanceFactor == -2) { // Left subtree is greater than right subtree
//         if (leftBalanceFactor < 0) {
//             rotateRight(start->left);
//         } else if (leftBalanceFactor == 1) {
//             rotateLeft(start->left->right);
//             rotateRight(start->left);
//         }
//     }
    
//     // Continue recursing up the BST
//     balanceTree(start->parent); 
// }

/**
 * rotateLeft(Node* start)
 * Rotate the subtree to the left at start and update the affected
 * children/parents pointers, heights, and subtree sizes
 * Input: Node* start
 * Output: none
 */
// void BST::rotateLeft(Node* start) {
//     Node* parent = start->parent;
//     cout << "Left Start Key: " << start->key << endl;
//     cout << "Left Parent Key: " << parent->key << endl;
//     // Update children of start and start's parent
//     if (start->left != NULL) {
//         // Set the parent's right child to start's left child
//         parent->right = start->left;
        
//         // Update parent's subtreeSize (pushing parent down BST)
//         parent->setSubtreeSize(parent->getSubtreeSize() - (start->getSubtreeSize() + 1) 
//                                + (start->left->getSubtreeSize() + 1));
//         // Update start's subtreeSize (pushing start up BST)
//         start->setSubtreeSize(start->getSubtreeSize() + parent->getSubtreeSize());
        
//         // Update height of parent
//         if (parent->left != NULL) {
//             parent->setHeight(max(parent->left->getHeight(), start->left->getHeight()) + 1);
//         } else {
//             parent->setHeight(start->left->getHeight() + 1);
//         }
//     } else { // start->left is NULL
//         parent->right = NULL;
//         // Update parent's subtreeSize (pushing parent down)
//         parent->setSubtreeSize(parent->getSubtreeSize() - 
//                                (start->getSubtreeSize() + 1));
//         // Update start's subtreeSize (pushing start up)
//         start->setSubtreeSize(start->getSubtreeSize() + 
//                               (parent->getSubtreeSize() + 1));
//         // Check if parent has a left child
//         if (parent->left != NULL) {
//             parent->setHeight(parent->left->getHeight() + 1);
//         } else {
//             parent->setHeight(1);
//         }
//     }
//     // Set the left child of start to its parent
//     start->left = parent;
//     if (parent->parent != NULL) {
//         parent->parent->left = start;
//     }
    
//     // Update parents of start and start's parent
//     // Check if start's parent is the root
//     if (parent == root) {
//         start->parent->parent = start;
//         root = start;
//         root->parent = NULL;
//     } else {
//         start->parent = parent->parent;
//         start->left->parent = start;
//     }
    
//     // Update parents of subtree roots in start and start parent's children
//     if (start->left->left != NULL) {
//         start->left->left->parent = start->left; // Leftmost child of start
//     }
//     if (start->left->right != NULL) {
//         start->left->right->parent = start->left; // Middle swapped child
//     }
    
//     if (start->right != NULL) {
//         start->right->parent = start; // Rightmost child of start
//     }
// }

/**
 * rotateRight(Node* start)
 * Rotate the subtree to the right at start and update the affected
 * children/parents pointers, heights, and subtree sizes.
 * Input: Node* start
 * Output: none
 */
// void BST::rotateRight(Node* start) {
//     Node* parent = start->parent;
//     cout << "Right Start key: " << start->key << endl;
//     cout << "Right Parent key: " << parent->key << endl;
//     // Update children of start and start's parent
//     if (start->right != NULL) {
//         // Set the parent's left child to start's right child
//         parent->left = start->right;
        
//         // Update parent's subtreeSize (pushing parent down BST)
//         parent->setSubtreeSize(parent->getSubtreeSize() - (start->getSubtreeSize() + 1) 
//                                + (start->right->getSubtreeSize() + 1));
//         // Update start's subtreeSize (pushing start up BST)
//         start->setSubtreeSize(start->getSubtreeSize() + parent->getSubtreeSize());
        
//         // Update height of parent
//         if (parent->right != NULL) {
//             parent->setHeight(max(parent->right->getHeight(), start->right->getHeight()) + 1);
//         } else {
//             parent->setHeight(start->right->getHeight() + 1);
//         }
//     } else { // start->right is NULL
//         parent->left = NULL;
//         // Update parent's subtreeSize (pushing parent down)
//         parent->setSubtreeSize(parent->getSubtreeSize() - 
//                                (start->getSubtreeSize() + 1));
//         // Update start's subtreeSize (pushing start up)
//         start->setSubtreeSize(start->getSubtreeSize() + 
//                               (parent->getSubtreeSize() + 1));
//         // Check if parent has a right child
//         if (parent->right != NULL) {
//             parent->setHeight(parent->right->getHeight() + 1);
//         } else {
//             parent->setHeight(1);
//         }
//     }
//     // Set the right child of start to its parent
//     start->right = parent;
//     if (parent->parent != NULL) {
//         parent->parent->right = start;
//     }
    
//     // Update parents of start and start's parent
//     // Check if start's parent is the root
//     if (parent == root) {
//         start->parent->parent = start;
//         root = start;
//         root->parent = NULL;
//     } else {
//         start->parent = parent->parent;
// //         parent = parent->parent;
//         cout << "Right - Parent: " << parent->key << endl;
//         cout << "start->parent: " << start->parent->key << endl;
//         start->right->parent = start;
//     }
    
    
//     // Update parents of subtree roots in start and start parent's children
//     if (start->right->right != NULL) {
//         start->right->right->parent = start->right; // Leftmost child of start
//     }
//     if (start->right->left != NULL) {
//         start->right->left->parent = start->right; // Middle swapped child
//     }
    
//     if (start->left != NULL) {
//         start->left->parent = start; // Rightmost child of start
//     }
    
//     printTree();
// }

/**
 * rotateRightLeft(Node* start)
 */
// void BST::rotateRightLeft(Node* start) {
    
// }

/**
 * rotateLeftRight(Node* start)
 */
// void BST::rotateLeftRight(Node* start) {
    
// }

/**
 * calculateBalanceFactor(Node* start);
 * Calculate the balance factor between the left and right node.
 * Input: Node* left and right
 * Output: int balance factor
 */
// int BST::calculateBalanceFactor(Node* start) {
//     int balanceFactor = 0;
//     Node* leftChild = start->left;
//     Node* rightChild = start->right;
    
//     int leftChildHeight = (leftChild == NULL) ? 0 : leftChild->getHeight();
//     int rightChildHeight = (rightChild == NULL) ? 0 : rightChild->getHeight();
    
//     balanceFactor = rightChildHeight - leftChildHeight;
    
//     return balanceFactor;
// }