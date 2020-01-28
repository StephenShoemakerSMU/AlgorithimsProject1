//This file parses the documents and inserts them into an Index
//Written by Alexander Clark
#ifndef DOCUMENTPARSE_H
#define DOCUMENTPARSE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <stdlib.h>
#include <map>
#include "fioavltree.h"
#include "indexavltree.h"
#include "sanitizer.h"
#include "indexentry.h"
#include "index.h"
#include "vector"
using namespace std;

class DocumentParse
{
private:
    const char *initial_Directory;
    int num_of_Cases;
    int total_Words;
    int u_Words;
    vector<vector<string>>word_List_Master;
    vector<string> case_Names;
    vector<string> case_Words;

public:
    DocumentParse();
    void select_initial_Dir(const char*);
    void accessFiles(const char*);
    void inputIntoIndex(Index*, Sanitizer*);
    void unique_Word_Counter();
    map<string, int> single_Document_Info(string, Sanitizer*);
    map<string,int> read_through(string, Sanitizer*);
    void collect_stats();
    void print_stats();
    void read_into_mmap();
    ~DocumentParse();
};

#endif // DOCUMENTPARSE_H
