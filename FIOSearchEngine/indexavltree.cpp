#include "indexavltree.h"
#include "mmaping.h"
#include "cstring"


IndexAvlTree::IndexAvlTree(){
}

IndexAvlTree::~IndexAvlTree(){
    saveIndex();
}
IndexEntry& IndexAvlTree::get(string searchString){

    sanitizer->sanitize(searchString);
    IndexEntry searchEntry(searchString);

    //This is the way to do it with the superior persistent Index
    /*if(indexTree.contains(searchString) && !(indexTree.get(searchEntry).hasBeenReadFromPersitentIndex())){
        indexTree.get(searchEntry).changeReadIn();

        parsePersistentEntry(indexTree.get(searchEntry));

    }*/


    return indexTree.get(searchEntry);
}

IndexEntry& IndexAvlTree::get(IndexEntry& searchString){
    return this->get(searchString.getWord());
}


bool IndexAvlTree::contains(string searchString){
    sanitizer->sanitize(searchString);
    IndexEntry searchEntry(searchString);
    return indexTree.contains(searchEntry);
}

void IndexAvlTree::addEntry(IndexEntry &newEntry){
    if(indexTree.contains(newEntry)){
        for(auto newEntryDocIter = newEntry.getDocs().begin(); newEntryDocIter != newEntry.getDocs().end(); newEntryDocIter++){
                indexTree.get(newEntry).addDocs(newEntryDocIter->first, newEntryDocIter->second);
        }
    }else{
        indexTree.insert(newEntry);
        incrementWordCount();
    }
}



vector<IndexEntry> IndexAvlTree::getDataAsVector(){
    return indexTree.getDataAsVector();
}


/*
 *
 * This is a faster way to do an Index, apparantly its not kosher though
 * thats pretty neat
 * Instead its all going to be shoved into one big dumb index like Cambodian prison :/
 *
void IndexAvlTree::saveIndex(){
    vector<IndexEntry> dataSet = indexTree.getDataAsVector();
    ofstream persistentIndex;
    persistentIndex.open("SrcFiles/PersistentIndex/persistentIndex.txt");
    for(int dataIter = 0; dataIter < dataSet.size(); dataIter++){
        string currWord = dataSet.at(dataIter).getWord();
        persistentIndex << currWord << endl;
        if(indexTree.get(dataSet.at(dataIter)).hasBeenReadFromPersitentIndex()){
            ofstream individualEntry;
            individualEntry.open("SrcFiles/PersistentIndex/Entries/" + dataSet.at(dataIter).getWord() + ".txt" );
            map<Document, int> entryMap = dataSet.at(dataIter).getDocs();
            for(auto mapIter = entryMap.begin(); mapIter!= entryMap.end(); mapIter++){
                Document doc = mapIter->first;
                individualEntry << doc.getDocPath() << "|" << mapIter->second << endl;
            }
            individualEntry.close();
        }
    }
    persistentIndex.close();

    persistentIndex.open("SrcFiles/PersistentIndex/docs.txt");
    set<Document> docs = this->getDocs();
    for(auto docSetIter = docs.begin(); docSetIter!=docs.end(); docSetIter++){
        Document currDoc = *(docSetIter);
        persistentIndex << currDoc.getDocPath() << endl;
    }
    persistentIndex.close();
}


void IndexAvlTree::loadIndex(){
    ifstream docInput;
    docInput.open("SrcFiles/PersistentIndex/docs.txt");
    cout << "Parsing persistent docs list" << endl;
    while(docInput.good()){
        string currLine;
        getline(docInput, currLine);
        Document newDoc(currLine);
        addParseDoc(newDoc);
        incrementDocumentCount();
    }
    docInput.close();
    cout << "Finished parsing persistent docs" << endl;
    ifstream entryInput;
    entryInput.open("SrcFiles/PersistentIndex/persistentIndex.txt");
    cout << "Parsing persistent words" << endl;
    string currLine;
    getline(entryInput, currLine);
    while(entryInput.good()){
        IndexEntry newEntry(currLine);
        addEntry(newEntry);
        getline(entryInput,currLine);

    }
    cout << "Finished Parsing Persistent words" << endl;
    entryInput.close();

}
*/


