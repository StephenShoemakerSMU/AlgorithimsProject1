//This class is what the Index stores on an individual bases
//Every entry in the index should have a word and a set
//of documents in which the word appears

//Written by Stephen Shoemaker and Alexander Clark
//Its set of documents should be able to be accessed using a get method
//Documents are also able to be added to an individual node
#ifndef INDEXENTRY_H
#define INDEXENTRY_H

#include <string>
#include <map>
#include <FIODocument.h>
using namespace std;
class IndexEntry
{    
    private:
        bool readInFromIndex;
        string word;
        map<FIODocument, int> docMap;

    public:
        IndexEntry();
        IndexEntry(string);
        IndexEntry(const IndexEntry&);
        IndexEntry(IndexEntry&);

        IndexEntry& operator=(const IndexEntry&);
        IndexEntry& operator=(IndexEntry&);

        bool hasBeenReadFromPersitentIndex(){return readInFromIndex;}
        void changeReadIn(){readInFromIndex = true;}

        bool operator==(const IndexEntry&)const ;
        bool operator<(const IndexEntry&) const;

        const string getWord()const ;
        const map<FIODocument, int>& getDocs();
        void addDocs(FIODocument, int);
        void addDocMap(map<FIODocument,int>);

};

#endif // INDEXENTRY_H
