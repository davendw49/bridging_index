#ifndef DATA_CONVERSE_HASH_GETFILENAME_H
#define DATA_CONVERSE_HASH_GETFILENAME_H

// Get the files name and print them into specific file

#include <sys/uio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <unistd.h>
#include "dirent.h"
// #include <direct.h>
#include <unistd.h>
#include <string>

using namespace std;

string getPath();                                         // get current file path
void GetFileName(string path, vector<string> &filesName); // get file list
void getFileName(const string &type);                     // get filename via a txt file

#endif // DATA_CONVERSE_HASH_GETFILENAME_H
