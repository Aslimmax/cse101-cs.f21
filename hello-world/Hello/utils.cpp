// File: utils.h
// This file has utility functions, for the Hello World test.
// 
// C. Seshadhri, Jan 2020
// 

#include <string>
#include <cstring>

// function genString:
//     input: string repeat, supposed to be an int
//     output: string with "Hello world " repeated input number of times. There is no new line at the end.
//    
//    The function first converts repeat into an int. If that fails, the number of repetitions is set to zero.

using namespace std;

string genString(string repeat)
{
    string to_return; // return value
    int rep = stoi(repeat); // convert input string into corresponding int
    for(int i=0; i < rep; i++) //loop for repeat times
        to_return = to_return + "Hello world "; // concatenate "Hello world " to return value. Note additional space at the end of string
    if (to_return.length() > 0) // string is non-empty
        to_return.pop_back(); // delete last character, which is an extra space
    return to_return;
}

