//Figure It Out
//Written by Stephen Shoemaker
//This document class stores three things
//a file name, a path to the file, and the amount
//of times a certain word appears in the file

//This class will be stored by an individual Entry in either Index
//Therefore the word itself is not stored in this class

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

using namespace std;

class FIODocument
{
    private:
        string docPath;
        int wordCount;
    public:
        FIODocument();
        FIODocument (string);
        FIODocument(string, int);
        FIODocument(const FIODocument&);

        FIODocument& operator=(const FIODocument&);

        bool operator ==(const FIODocument&)const ;
        bool operator<(const FIODocument&)const ;

        string getDocPath();
        int getWordCount(){return wordCount;}
        void increaseWordCount(int newCount){wordCount += newCount;}
};

#endif // DOCUMENT_H
