//Figure it Out
//Written by Stephen Shoemaker

//This is an AVLTree implementation of the index class
//The Avl Tree stores Entries

#ifndef INDEXAVLTREE_H
#define INDEXAVLTREE_H

#include <index.h>
#include <fioavltree.h>
#include <string>
#include <indexentry.h>
#include <set>
#include <FIODocument.h>
#include <vector>
#include <fstream>
using namespace std;
class IndexAvlTree : public Index{
    private:
        FIOAvlTree<IndexEntry> indexTree;
    public:
        IndexAvlTree();

        virtual ~IndexAvlTree();
        virtual IndexEntry& get(string);
        virtual IndexEntry& get(IndexEntry&);
        virtual bool contains(string);
        virtual void addEntry(IndexEntry&);

        virtual vector<IndexEntry> getDataAsVector();
};

#endif // INDEXAVLTREE_H
