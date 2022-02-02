#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include "utils.h"
#include <string>

using namespace std;
// using namespace utils; // for the function defined in utils

int main(int argc, char** argv)
{
    if (argc < 3) // must provide two arguments as input
    {
        throw std::invalid_argument("Usage: ./hello <INPUT FILE> <OUTPUT FILE>"); // throw error
    }

    ifstream input; // stream for input file
    ofstream output; // stream for output file

    input.open(argv[1]); // open input file
    output.open(argv[2]); // open output file

    string repeat; // to store number of repetitions
    string to_print; // the desired output
    while(getline(input,repeat)) // get next line of input, store as repeat
    {
        to_print = genString(repeat); // call function to get "Hello world" repeated 
        output << to_print << endl; // write string to file, and add new line
    }
    input.close(); //close input stream
    output.close(); // close output stream
}
