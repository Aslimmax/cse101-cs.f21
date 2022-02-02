/**
 * Filename: wordrange.cpp
 * 
 * This is the main file for the Assignment deatiled in range_queries_avl.pdf
 * 
 * After running make, the usage is
 *     ./wordrange <INPUT_FILE> <OUTPUT_FILE>
 * 
 * Input:
 * Output:
 * 
 * Look at the associated pdf (range_queries_avl.pdf) in this directory
 * for more details
 * 
 * A. Lim, November, 2021
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "bst.h"
#include <cstring>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) { // Must provide two arguments as input
        throw std::invalid_argument("Usage: ./wordrange <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    
    /**
     * Input/output processing code
     */
    ifstream input; // Initialize stream for input file
    ofstream output; // Initiailize stream for output file
    
    input.open(argv[1]); // Open input file
    output.open(argv[2]); // Open output file
    
    string command = ""; // Store the next command and operator
    char *com, *valstr, *op; // For use with strtok, strtol
    string val1 = ""; // First value from the command
    string val2 = ""; // Optional second value if performing range queries
    
    BST myBST; // initializing the linked list
    
    // Loop through input file
    while(getline(input, command)) {
        if (command.length() == 0) // command is empty
            continue;
        
        com = strdup(command.c_str()); // First copy string into a "C-style" string
        op = strtok(com, " \t"); // Tokenize command on whitepsace, first token is operation
        
        valstr = strtok(NULL, " \t"); // Next token is value, as string
        if (valstr != NULL) { // Check if an argument was passed
            // Convert initial portion of valstr into a string
            string temp1(valstr);
            val1 = temp1;
        }
        
        valstr = strtok(NULL, " \t"); // Final token is the optional second value
        if (valstr != NULL) { // Check if an argument was passed
            // Convert initial portion of valstr into a string
            string temp2(valstr);
            val2 = temp2;
        }
        
        // Insert val1 into BST
        if(strcmp(op, "i") == 0) {
            // First determine if val1 is in the BST. If it isn't, insert
            // val1 into the tree
            if (myBST.find(val1) == NULL) {
                myBST.insert(val1);
            }
        }
        
        // Count the number of strings (currently stored) that are
        // lexicographically between val1 and val2
        if (strcmp(op, "r") == 0) {
            // Initailize var that stores the number of strings between
            // val1 and val2
            int rangeSize = 0;
            // Recurse through the tree and determine the number of
            // string that fall between val1 and val2
            rangeSize = myBST.numItemsInRange(val1, val2);
            
            // Write rangeSize back to output file
            output << rangeSize << endl;
        }
        
        // Free allocated memory from strdup
        free(com);
    }
        
    myBST.deleteBST(); // Delete the tree from memory
    
    // Close input/output streams
    input.close();
    output.close();
    
    return 0;
}