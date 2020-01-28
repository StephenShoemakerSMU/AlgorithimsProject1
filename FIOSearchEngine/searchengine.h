// This class presents a user interface for the user to use the index and load in documents
//Written by Stephen Shoemaker
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "sanitizer.h"
#include "index.h"
#include "indexavltree.h"
#include "hashindex.h"
#include "indexentry.h"
#include "FIODocument.h"
#include "string"
#include "documentparse.h"
#include <iostream>
#include "chrono"
#include <fstream>


using namespace std;
using namespace chrono;
class SearchEngine{
    private:
        Sanitizer* sanitizer;
        Index* index;
        DocumentParse* parser;

        void maintenance();
        void statistics();
        void search();

        bool isChar(char);

        void maintenanceMenu();
        void displayBaseMenu();
        void searchMenu();
        void statisticsMenu();

        void getSearchResult(string);
        
        void displayIndividualSearchResult(string);
        void searchResponse();
        void displayDoc(string);

        vector<pair<FIODocument,double>> castToVector(map<FIODocument,int>);

        void addIndex();
    public:
        SearchEngine();
        ~SearchEngine();

        void speedTest(string, string);

        void experiment();

        void startUI();
};

#endif // SEARCHENGINE_H
