#include "hashindex.h"
#include "hashmap.h"
#include "hashnode.h"
#include "cstring"
#include "mmaping.h"

//Hash Index constructor
HashIndex::HashIndex(){
}

//Hash Index destructor
HashIndex::~HashIndex(){
}

IndexEntry& HashIndex::get(string searchKey){
    sanitizer->sanitize(searchKey);
    IndexEntry searchEntry(searchKey);

    return table.get(searchKey);
}

IndexEntry& HashIndex::get(IndexEntry& searchString){
    return this->get(searchString.getWord());
}

bool HashIndex::contains(string key){
    sanitizer->sanitize(key);
    return table.contains(key);
}

void HashIndex::addEntry(IndexEntry& newEntry){
    if(table.contains(newEntry.getWord())){
        for(auto newEntryDocIter = newEntry.getDocs().begin(); newEntryDocIter != newEntry.getDocs().end(); newEntryDocIter++){
            table.get(newEntry.getWord()).addDocs(newEntryDocIter->first, newEntryDocIter->second);
        }
    } else {
        table.put(newEntry.getWord(), newEntry);
        incrementWordCount();
    }
}

vector<IndexEntry> HashIndex::getDataAsVector(){
    return table.intoVec();
}



