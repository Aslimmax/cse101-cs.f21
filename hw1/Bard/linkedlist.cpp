// Filename: linkedlist.cpp
//
// Contains the class LinkedList that represents a linked list. This contains some basic operations, 
// such as insert, delete, find, length, as well as some advanced functions, such as reverse, 
// removeDuplicates, and sortLists.
//
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020
// Andrew Lim, October 2021

#include "linkedlist.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// Default constructor sets head and tail to null
LinkedList :: LinkedList() {
    head = NULL;
}

// insert(string val): Inserts the string val into list, at the head of the list. Note that there may be multiple copies of val in the list.
// Input: String to insert into the linked list
// Output: Void, just inserts new Node
void LinkedList :: insert(string val) {
    Node* to_add = new Node; // creates new Node
    to_add->word = val; // set the word to hold input val
	to_add->frequency = 1; // set the frequency of the Node to 1
    
    to_add->next = head; // make to_add point to existing head
    head = to_add; // set head to to_add
}

// find(string val): Finds a Node with word "val"
// Input: string to be found
// Output: a pointer to the first Node in the list containing val, if it exists. Otherwise, it returns NULL.
Node* LinkedList :: find(string val) {
    Node* curr = head; // curr is the current Node as it progresses through the linked list. Initailized to head to start at the head of the list.
    while(curr != NULL) { // loop over list
        if (curr->word == val) // found val, so return curr
            return curr;
        curr = curr->next; // otherwise, proceed through the list
    }
    // if loop terminates, val not found
    return NULL;
}

// deleteNode(string val): Delete a Node with word val, if it exists. Otherwise, do nothing
// Input: string to be removed
// Output: pointer to Node that was deleted. If no Node is deleted, return NULL. If there are multiple Nodes with val, 
// only the first Node in the list is deleted
Node* LinkedList :: deleteNode(string val) {
    Node* prev = NULL;
    Node* curr = head;
    
    while(curr != NULL) { // loop over list
        if (curr->word == val) // we found Node with val, so break
            break;
        // otherwise, proceed through the list
        prev = curr; // move prev by one Node
        curr = curr->next; // move curr by one Node
    }
    
    // At this point, curr points to Node with val. If curr is NULL, then val is not in the list
    if (curr == NULL) // val not found
        return NULL;
    
    // val is in the list and curr is not NULL. If prev is null, then curr is head. So we delete head directly.
    // Otherwise, we delete the Node after prev.
    if (prev == NULL) // we need to delete head
        head = head->next; // delete head
    else // we delete Node after prev. 
        prev->next = curr->next; // make prev point to Node after curr. This removes curr from list
    
    return curr;
}

// Deletes every Node to prevent memory leaks.
// Input: None
// Output: Void, just delets every Node in the list
void LinkedList :: deleteList() {
    // curr is the current Node as it progresses through the linked list. Initialized to head to 
    // start at the head of the list
    Node* curr = head; 
    Node* temp = NULL;
    
    // curr will loop over the list. At every iteration, we first store a pointer 
    // to the next Node, and then delete the current Node.
    while(curr != NULL) { // loop over list
        temp = curr->next; // store pointer to next Node in the list
        delete(curr); // delete the current Node
        curr = temp; // update curr to proceed through the list
    }
    // the list is empty now. Set head to NULL to prevent unwanted access to deleted data
    head = NULL;
    
    return;    
}

// Prints list in order
// Input: None
// Output: string that has all elements of the list in order
string LinkedList :: print() {
    string list_str = ""; // string that will hold the contents of the list 
    // curr is the current Node as it progresses through the linekd list. Initialized to head to 
    // start at the head of the list
    Node* curr = head; 
    
    // curr will loop over the list. It prints the content of curr, and then moves curr to the next Node
    while(curr != NULL) { // loop over list
        list_str = list_str + curr->word + " "; // append string with current Node's data
        curr = curr->next; // proceed through list
    }
    if (list_str.length() > 0) // string is non-empty
        list_str.pop_back(); // remove the last (extra) space from string
    
    return list_str;
}

// Computes the length of the linked list
// Input: None
// Output: Int, length of list
int LinkedList :: length() {
    int length = 0; // initialize length to zero
    // curr is the current Node as it progresses through the linked list. Initialized to head to 
    // start at the head of the list
    Node* curr = head; 
    
    while(curr != NULL) { // loop over list
        length++; // increment length
        curr = curr->next;
    }
    
    return length;
}

// Helper function of reverseList(Node*) that sets the new head of the reversed list
// Input: None
// Output: None
void LinkedList :: reverse() {
    head = reverseList(head);
}

// Reverse the list starting from start
// Input: Start, Node to start the reversal process
// Output: The head Node of the reversed list
Node* LinkedList :: reverseList(Node* start) {
    if (start == NULL || start->next == NULL) { // base case: the list is empty or the next element is NULL
        return start;
    }
    
    Node* new_head = reverseList(start->next); // recursive call to find the head of the reversed list
    
    start->next->next = start; // set the new head's next node to point to the original head
    
    start->next = NULL; // set the original head's next node to NULL
    
    return new_head;
}

// Removes duplicate Nodes and increments the frequency of the base Node as each duplicate is deleted
// Input: None
// Output: None
void LinkedList :: removeDuplicates() {
	if (length() == 0) { // ensure that the list is not empty
		return; 
	}
	
	Node* curr = head; // curr is the current Node as it progresses through the linked list. Initialized to head to start at the head of the list
	Node* tempCurr = NULL; // will temporarily store the value of curr when a duplicate gets deleted
	// initialize to the start. This will act as the base Node and will have its frequency changed if there duplicates of it (same word string). 
	// At the end of the list, baseNode may have updated the frequency of every Node if it had duplicates
	Node* baseNode = head; 
	Node* prev = NULL; // need to keep track of the previous Node to properly iterate through the list after a deletion
	
	while(baseNode != NULL) { // loop through all words in the list
		while(curr != NULL) { // loop through all words in the list (deleting duplicate Nodes and updating baseNode frequency)
			if (curr->word == baseNode->word && curr != baseNode) { // found a duplicate
				tempCurr = curr->next; // temporarily store curr's next Node in tempCurr
				prev->next = curr->next; // make prev point to the Node after curr. This will remove curr from the list
				delete(curr); // delete the duplicate from the list
				baseNode->frequency = baseNode->frequency + 1; // increment the baseNode's frequency by 1 after deleting the duplicate
				
				curr = tempCurr; // move curr up by one Node
			} else { // Move onto the next Node if there was no match
				prev = curr; // move prev up by one Node
				curr = curr->next; // move curr up by one Node		
			}		
		}
		baseNode = baseNode->next; // move baseNode up by one Node		
		curr = baseNode; // reset curr to point back to baseNode
		prev = NULL;
	}

}

// Sorts the linked list in increasing order of frequency and decreasing lexicographic order. Utilizes Bubble Sort.
// LinkedList :: reverseList() will be used to reverse the frequency and lexicographic order.
// Input: None
// Output: None
void LinkedList :: sortLists() {
    // Initialize to false. Will help determine if a swap was performed during the sort, and if one wasn't 
    // exit out of the loop and end the swap function.
    bool swapped = false; 
    Node* curr = NULL; // Initialized to null.    
    int wordsListLength = length(); // get the length of the linked list
    
    for(int i = 0; i <= wordsListLength; i++) {
        curr = head; // Set curr to head. As the outer loop progresses, it will visit every single node
        swapped = false; // Set to false at the beginning of each outer iteration

        for(int j = 0; j < wordsListLength - i - 1; j++) {
            Node* leftNode = curr; // set leftNode (from outer loop) to curr
            Node* rightNode = curr->next; // set rightNode (from innerLoop) to curr's next node
            int leftNodeFrequency = leftNode->frequency; // store the frequency of the leftNode
            int rightNodeFrequency = rightNode->frequency; // store the frequency of the rightNode

            if (leftNodeFrequency > rightNodeFrequency) { // the leftNode has a higher frequency than the rightNode
                swapFrequencies(leftNode, rightNode); // swap the frequencies
                swapWords(leftNode, rightNode); // swap the words
                swapped = true;
            }
            else if (leftNodeFrequency == rightNodeFrequency) { // the leftNode and rightNode has the same frequency, so order lexicographically
                if (leftNode->word < rightNode->word) { // the leftNode has a higher lexicographic order than the rightNode
                    swapFrequencies(leftNode, rightNode); // swap the frequencies
                    swapWords(leftNode, rightNode); // swap the words
                    swapped = true;
                }
            }
            curr = curr->next; // move curr up by one Node
        }
        if (swapped == false) { // check to see if no swaps were made. If there were none, then the linked list has been sorted
            break;
        }
    }
}

// Swap the word string between two Nodes (data only, not swapping the Nodes)
// Input: Two nodes, leftNode and rightNode
// Output: None
void LinkedList :: swapWords(Node*& leftNode, Node*& rightNode) {
    string tempString = rightNode->word; // intialize tempString to hold onto rightNode's word
    rightNode->word = leftNode->word; // set the rightNode's word to the leftNode's word
    leftNode->word = tempString; // set the leftNode's word to tempString (rightNode's word)
}

// Swap the frequency between two Nodes (data only, not swapping the Nodes)
// Input: Two nodes, leftNode and rightNode
// Output: None
void LinkedList :: swapFrequencies(Node*& leftNode, Node*& rightNode) {
    int tempFrequency = rightNode->frequency; // intialize tempFrequency to hold onto rightNode's frequency
    rightNode->frequency = leftNode->frequency; // set the rightNode's frequency to the leftNode's frequency
    leftNode->frequency = tempFrequency; // set the leftNode's frequency to tempFrequency (rightNode's frequency)
}

// Find the Node in the list that is val ranked
// Input: val, the ranking of the Node in the list
// Output: String, the word that is ranked val
string LinkedList :: findRankNode(int val) {
    int counter = 0; // initialize a counter to track the current place in the loop
    Node* curr = head; // intialize curr to the head of the list. Will be used to iterate through the list
    
    if (length() == 0) { // check to see that the list is not empty
        return "-"; 
    }
    
    while (curr != NULL) { // loop through the list
        if (counter >= val) { // we have found the Node that is ranked val
            break;
        }
        // Otherwise, continue iterating through the list
        counter++;
        curr = curr->next; // move curr up by one Node;
    }
    
    // If terminated out of the loop without break, curr is either empty or was not found 
    // (the list is empty or the word does not exist)
    if (curr == NULL) {
        return "-";
    }
    
    return curr->word; // return the word that is ranked val
}
