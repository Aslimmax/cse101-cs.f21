// Filename: bard.cpp
//
// This is the main file for the Assignment detailed in hw_shakespeare.pdf
//
// After running make, the usage is:
//    ./bard <INPUT_FILE> <OUTPUT_FILE>
// 
// Input (from the assignment specs): "The input file contains a new query. The query is a pair of numbers: LENGTH RANK. 
// The first number is the length of the word, the second number is the rank, which starts from 0. The ranking is done 
// in decreasing order of frequence, and increasing lexicographic order."
//
// Output (from the assignment specs): "The output for each line is the corresponding word. If no word exists, the output is '-'."
//
// Look at the associated pdf (hw_shakespeare.pdf) in this directory for more details.
//
// Andrew Lim, October 2021

#include <iostream>
#include "linkedlist.h"
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {// must provide two arguments as input
      throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }
    string word = ""; // will store the word in the input file
    int maxWordLength = 0; // store the length of the longest word in the text file
    
    ifstream input; // stream for input file
    ofstream output; // stream for output file
	
    ifstream shakespeareText("shakespeare-cleaned5.txt"); // open the full text of all compositions of Shakespeare
    // Iterate shakespeareText to find the longest word in the file
    while (getline(shakespeareText, word)) {
        int wordLen = word.length(); // store the length of the current word
        if (wordLen > maxWordLength) { // if we have found a word with a longer length than the previous maxWordLength
            maxWordLength = wordLen; // update the max word length
        }
    }
    shakespeareText.close(); // close the input text file
    
    /*
     * With the longest length of all the words in the text file, we can create our array of LinkedLists
     */
    // initailize an array of LinkedLists to hold words that are at most maxWordLength characters long
    LinkedList wordsList[maxWordLength + 1]; 

    shakespeareText.open("shakespeare-cleaned5.txt"); // reopen the input text file
    // Each LinkedList in wordList at array index n stores all words of length n
    while (getline(shakespeareText, word)) { // loop through shakespeareText
          int wordLen = word.length(); // get the length of the current word
          wordsList[wordLen].insert(word); // insert the word into its corresponding LinkedList (including duplicates)
    }
	
    int wordsListSize = sizeof(wordsList)/sizeof(wordsList[0]); // store the length of the wordsList array

    /*
     * With all of the words in their respective linked list, we have to go through each linked list and
     * 1. remove duplicate words
     * 2. sort the list
     * 3. reverse the list (the list order will become decreasing order of frequency and increasing lexicographic order)
     */
    for(int i = 0; i < wordsListSize; i++) {
        wordsList[i].removeDuplicates();
        wordsList[i].sortLists();
        wordsList[i].reverse();
    }
    
    /*
     * With the lists sorted now, we need to handle input from the file and export the results to the output file
     */
    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file
    
    int inputFileWordLength = 0, inputFileRank = 0; // initialize int variables to store the query numbers from the input file
    while (input >> inputFileWordLength >> inputFileRank) { // loop through input file
        string outputString = ""; // initalize string var to write back to the output file
        // Check that:
        // 1. the queried word length is not greater than the largest maxWordLength and
        // 2. the queried word length is not negative and
        // 3. the queried rank is not negative
        if ((inputFileWordLength > maxWordLength || inputFileWordLength < 0) || inputFileRank < 0) { 
            outputString = "-"; // the word will not exist in this list
        } 
        else {
            // find the word corresponding to the input length and rank
            outputString =  wordsList[inputFileWordLength].findRankNode(inputFileRank);
        }
        output << outputString << "\n"; // write the output string to the output file
    }
    
    // Delete all linked lists
    for(int i = 0; i < wordsListSize; i++) { // loop through all linked lists
        wordsList[i].deleteList(); // delete the linked list
    }

    // Close the input and output files
    input.close();
    output.close(); 

    return 0;
}
