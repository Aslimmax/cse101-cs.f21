// File: utils.h
// This header file has utility functions, for the Hello World test.
// 
// C. Seshadhri, Jan 2020
// 

#ifndef UTILS
#define UTILS

#include <string>
#include <cstring>
using namespace std;

// function genString:
//     input: string repeat, supposed to be an int
//     output: string with "Hello world " repeated input number of times. There is no new line at the end.
//    
//    The function first converts repeat into an int. If that fails, the number of repetitions is set to zero.

string genString(string repeat);

#endif
