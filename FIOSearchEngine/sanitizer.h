//This Sanitizer class takes a word and stems it
//Written by Stephen Shoemaker
#ifndef SANITIZER_H
#define SANITIZER_H

#include <string>
#include <map>
#include <fstream>
#include <set>
#include <iostream>
#include <porter2_stemmer.h>
using namespace std;

class Sanitizer
{
    private:

        map<string, string> sanitizeMap;
        set<string> stopWords;

        string sanitizeMapFile;
        string stopWordsFile;





        void lowerCase(string&);

        void stem(string&);


    public:

        Sanitizer();

        ~Sanitizer();

        bool isStop(string);

        bool sanitize(string&);

        void loadSanitizeMap();
        void loadStopWords();

        void saveSanitizeMap();
        void saveStopWords();
};

#endif // SANITIZER_H
