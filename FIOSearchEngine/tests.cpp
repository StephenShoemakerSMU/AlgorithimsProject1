#include "catch.hpp"
#include "fioavltree.h"
#include "index.h"
#include "indexavltree.h"
#include "indexentry.h"
#include "FIODocument.h"
#include "string"
#include "set"
#include <iostream>
#include "sanitizer.h"
#include "searchengine.h"
using namespace std;

void test(int input){
    cout << input << endl;
}


TEST_CASE("AVLTree", "[AVLTREE]"){
    FIOAvlTree<int> tree;


    SECTION("Insertion"){
        for(int index = 0; index < 100; index++)tree.insert(index);
        for(int index = 0; index < 100; index++)REQUIRE(tree.contains(index));
        tree.inOrder(test);
    }

}

TEST_CASE("AVLTree Index", "avlIndex"){
    Index* index = new IndexAvlTree();
    IndexEntry entry1("Apple");

    IndexEntry entry2("Apple");

    FIODocument doc1("./AppleConstitution.txt");
    FIODocument doc2("./toPlant.txt");
    FIODocument doc3("./Johnnytxt");
    entry1.addDocs(doc1,5);
    entry1.addDocs(doc2,7);
    entry2.addDocs(doc3,12);

    map<FIODocument,int> docSet;
    docSet.insert(pair<FIODocument,int>(doc1,5));
    docSet.insert(pair<FIODocument,int>(doc2,7));
    docSet.insert(pair<FIODocument,int>(doc3, 12));
    SECTION("Insertion"){
        index->addEntry(entry1);
        index->addEntry(entry2);
        REQUIRE(index->get("Apple").getDocs() == docSet);
    }

    delete index;
}

TEST_CASE("STEMMER", "[stemmer]"){
    Sanitizer sanitizer;
    string test = "RUNNING";
    string test2 = "running";
    string test3 = "runner";
    sanitizer.sanitize(test);
    sanitizer.sanitize(test2);
    sanitizer.sanitize(test3);


    sanitizer.saveSanitizeMap();
    sanitizer.saveStopWords();
    cout << test << " " << test2 << " " << test3 << endl;

}

TEST_CASE("Search Engine Controller", "[Controller]"){
    SearchEngine search;
}
