//This class parses in all information for memory mapping
//Made by Alexander Clark

#ifndef PARSING_H
#define PARSING_H

#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

class parsing {
public:
    int wordFreq;
    string wordStr;
    parsing() {}
    void countWords(int wordFreq, string wordStr);

    static char* openDoc(string);
//read word in as a string, keep track of frequency

private:
    ifstream readFile;

};





#endif // PARSING_H
