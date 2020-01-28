//Figure It Out
//Written by Alexander Clark

//This a Hash Table Implementation of the index class
//Hash Table stores entries


#ifndef HASHINDEX_H
#define HASHINDEX_H

#include <index.h>
#include <indexentry.h>
#include <string>
#include <vector>
#include <hashmap.h>
#include <sanitizer.h>

#include "hashmap.h"
#include "hashnode.h"

using namespace std;
class HashIndex: public Index{
public:
    HashIndex();

    virtual ~HashIndex();
    virtual IndexEntry& get(string);
    virtual IndexEntry& get(IndexEntry&);
    virtual bool contains(string);
    virtual void addEntry(IndexEntry&);

    virtual vector<IndexEntry> getDataAsVector();

private:
    HashTable<string, IndexEntry> table;
};

#endif // HASHINDEX_H
