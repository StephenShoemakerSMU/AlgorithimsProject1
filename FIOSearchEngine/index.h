//Figure it Out
//Pure Virtual class for the index
//An index should be capable of receiving entries to store,
//receiving new entries, and returning a set of documents in which
//some entries appear

//Also returns the amount of words indexed and the amount of
//documents indexed

//The Index should be capable of saving and loading a persistent index
#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <indexentry.h>
#include <vector>
#include <sanitizer.h>
#include <set>
#include <FIODocument.h>
using namespace std;
class Index
{
    private:
        int totalWordCount;
        int wordCount;
        int documentCount;
        set<FIODocument> parsedDocs;
        string persistentPath;
        
    public:

        void setPersistentPath(string newPath) {persistentPath = newPath;}
        string getPersistentPath(){ return persistentPath;}

        void parsePersistentEntry(IndexEntry&);

        Index();
        virtual ~Index();
        void incrementWordCount();
        void incrementDocumentCount();
        void incrementTotalWordCount(int increase){totalWordCount+= increase;}

        int getTotalWordCount(){return totalWordCount;}
        int getWordCount();
        int getDocumentCount();

        void addSanitizer(Sanitizer* newSan){ sanitizer = newSan;}

        virtual IndexEntry& get(string) = 0;
        virtual IndexEntry& get(IndexEntry&) = 0;
        virtual bool contains(string) = 0;
        virtual void addEntry(IndexEntry&) = 0;

        virtual void saveIndex();
        virtual void loadIndex();

        vector<pair<string, int>> getTop50Words();

        set<FIODocument> getDocs(){return parsedDocs;}

        virtual vector<IndexEntry> getDataAsVector() = 0;

        bool hasDocBenParsed(FIODocument);

        void addParseDoc(FIODocument);

        Sanitizer* sanitizer;
        
};

#endif // INDEX_H
