#include "indexentry.h"

IndexEntry::IndexEntry(){
    word = "";
    readInFromIndex = false;
}
IndexEntry::IndexEntry(string initWord){
    word = initWord;
    readInFromIndex = false;
}

IndexEntry::IndexEntry( const IndexEntry & cpy){
    word = cpy.word;
    if(cpy.docMap.size() != 0)
    docMap = cpy.docMap;
    readInFromIndex = cpy.readInFromIndex;
}

IndexEntry::IndexEntry(IndexEntry & cpy){
    word = cpy.word;
    if(cpy.docMap.size() != 0)
    docMap = cpy.docMap;
    readInFromIndex = cpy.readInFromIndex;
}

IndexEntry& IndexEntry::operator =(const IndexEntry& cpy){
    word = cpy.word;
    if(cpy.docMap.size() != 0)
    docMap = cpy.docMap;
    readInFromIndex = cpy.readInFromIndex;
    return *(this);
}

IndexEntry& IndexEntry::operator=(IndexEntry& cpy){
    word = cpy.word;
    if(cpy.docMap.size() != 0)
    docMap = cpy.docMap;
    readInFromIndex = cpy.readInFromIndex;
    return *(this);
}

bool IndexEntry::operator==(const IndexEntry& rhs)const {
    return(word.compare(rhs.word)== 0);
}

bool IndexEntry::operator <(const IndexEntry& rhs)const {
    return(word.compare(rhs.word) < 0);
}

const map<FIODocument, int>& IndexEntry::getDocs() {
    return docMap;
}

void IndexEntry::addDocs(FIODocument newDoc, int count){
    if(docMap.find(newDoc) == docMap.end()){
        docMap.insert(pair<FIODocument,int>(newDoc, count));
    }
}

void IndexEntry::addDocMap(map<FIODocument, int> newDocs){
    for(auto newDocIter = newDocs.begin(); newDocIter != newDocs.end(); newDocIter++){
        this->addDocs(newDocIter->first, newDocIter->second);
    }
}

const string IndexEntry::getWord()const {
    return word;
}
