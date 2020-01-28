#include "index.h"

Index::Index(){
    wordCount = 0;
    documentCount = 0;
    persistentPath = "SrcFiles/PersistentIndex.txt";
}

Index::~Index(){
    parsedDocs.clear();
}

void Index::incrementDocumentCount(){
    documentCount++;
}

void Index::incrementWordCount(){
    wordCount++;
}

int Index::getWordCount(){
    return wordCount;
}

int Index::getDocumentCount(){
    return parsedDocs.size();
}

void Index::addParseDoc(FIODocument docToAdd){
    parsedDocs.insert(docToAdd);
}

bool Index::hasDocBenParsed(FIODocument searchDoc){
    if(parsedDocs.size() == 0) return false;
    return(parsedDocs.find(searchDoc) != parsedDocs.end());
}

void Index::parsePersistentEntry(IndexEntry & entry){
    ifstream entryFile;
    entryFile.open("SrcFiles/PersistentIndex/Entries/" + entry.getWord() + ".txt");

    string path;
    string count;
    getline(entryFile, path,'|');
    getline(entryFile, count);
    FIODocument newDoc(path);

    this->get(entry.getWord()).addDocs(newDoc, stoi(count));
    getline(entryFile,path,'|');
    while(entryFile.good()){
        getline(entryFile,count);
        FIODocument newDoc(path);
        this->get(entry.getWord()).addDocs(newDoc,stoi(count));
        getline(entryFile,path,'|');
    }
}

void Index::loadIndex(){
    ifstream input;
    input.open(persistentPath.c_str());
    string currLine;
    getline(input,currLine);
    while(input.good()){
        IndexEntry newEntry(currLine);
        map<FIODocument,int> documents;
        getline(input,currLine, '|');
        while(currLine.compare("") != 0){
            string path = currLine;

            getline(input, currLine, '|');
            int frequency = stoi(currLine);
            incrementTotalWordCount(frequency);

            getline(input, currLine);

            FIODocument newDoc(path, stoi(currLine));
            documents.insert(pair<FIODocument,int>(newDoc, frequency));
            getline(input,currLine, '|');
            this->addParseDoc(newDoc);
        }
        newEntry.addDocMap(documents);
        this->addEntry(newEntry);
        getline(input,currLine);
        getline(input,currLine);
    }
    input.close();

}

void Index::saveIndex(){
    vector<IndexEntry> dataSet = this->getDataAsVector();
    ofstream persistentIndex;
    persistentIndex.open(persistentPath.c_str());
    for(auto dataIter = dataSet.begin(); dataIter != dataSet.end(); dataIter++){
        persistentIndex << dataIter->getWord() << endl;
        map<FIODocument, int> docs = dataIter->getDocs();
        for(auto docIter = docs.begin(); docIter != docs.end(); docIter++){
            FIODocument doc = docIter->first;
            persistentIndex << doc.getDocPath() << "|" << docIter->second  << "|" << doc.getWordCount() << endl;
        }
        persistentIndex << "|" << endl;
    }
    persistentIndex.close();
}

vector<pair<string, int>> Index::getTop50Words(){
    vector<pair<string,int>> output;
    vector<IndexEntry> data = this->getDataAsVector();
    for(int count = 0; count < 50; count++){
        auto currTop = data.begin();
        auto currIndex = data.begin();
        for(; currIndex != data.end(); currIndex++){
            if(currIndex->getDocs().size() > currTop->getDocs().size()){
                currTop = currIndex;
            }
        }
        output.push_back(pair<string,int>(currTop->getWord(),currTop->getDocs().size()));
        data.erase(currTop);
    }

    return output;
}
