// Filename: linkedlist.h
//
// Header file for the class LinkedList that represents a linked list abstract data type
//
// Japheth Frolick, August 2019
// C. Seshadhri, Jan 2020
// Andrew Lim, October 2021

#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

// node struct to hold data
struct Node {
    string word; // word string from Shakespeare's text
    int frequency; // number of occurences of the word
    Node* next;
};

class LinkedList {
    private:
        Node* head; // Stores head of linked list
    public:
        LinkedList(); // Default constructor sets head to null
        void insert(string); // Insert word into list
        Node* find(string); // Find word in list, and return pointer to node with that word. If there are multiple copies, this only finds one copy.
        Node* deleteNode(string); // Remove a node with word (if it exists), and return pointer to deleted node. This does not delete all nodes with the value.
        void deleteList(); // Deletes every node to prevent memory leaks and frees memory.
        string print(); // Construct string with data of list in order
        int length(); // Returns the length of the linked list
	
		// Advanced functions
        void reverse(); // Helper function of reverseList(Node*) that sets the new head of the reversed list
        Node* reverseList(Node* start); // Reverse the list starting from Node start
        void removeDuplicates(); // Remove duplicate Nodes (a Node with the same word as another). Increment the frequency of the base Node as a Node is deleted
        // Sorts the linked list in increasing order of frequency and decreasing lexicographic order. reverse()
        // will be used in tangent to set the order to DECREASING order of frequency and INCREASING lexicographic
        // order
        void sortLists(); 
        void swapWords(Node*&, Node*&); // Swap the word string between two Nodes
        void swapFrequencies(Node*&, Node*&); // Swap the frequency between two Nodes
        string findRankNode(int); // Find the word in the list that is val ranked
};

#endif
