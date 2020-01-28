//Figure It Out Hash Table Implementation
//This was written by Alexander Clark

#ifndef HASHMAP_H
#define HASHMAP_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unordered_set>
#include "hashnode.h"

using namespace std;

//templated for data types of key and value
template<typename kData, typename vData>
class HashTable{
public:

    int curr_tableSize;
    int index = 0;
    int numChains = 20; //test
    int hashNum = 0;
    //used to keep track of how big the table is getting so that we know when to reHash
    int growthRatio = 0;
    string word;
    kData key;
    vData value;

    //some magic hash values I found online
    static const size_t initial = 2166136261U;
    static const size_t hashPower = 16777619;

    //table & singly linked list constructor
    HashTable () {
        curr_tableSize = 128;
        size = 0;
        table = new HashNode<kData, vData> *[curr_tableSize];
        chainLink = new HashNode<kData, vData> *[numChains];

        //fill table with NULL
        for (int i = 0; i < curr_tableSize; i ++) {
            table[i] = nullptr;
        }
    }

    //table destructor
    ~HashTable() {
        for(int i = 0; i < curr_tableSize; i++) {
            //HashNode<kData, vData>* entry = nullptr;
            //entry = (table+ i);
            HashNode<kData, vData>* currEntry = table[i];
            HashNode<kData, vData>* nextEntry;
            while ((currEntry) != nullptr) {
                nextEntry = currEntry->getNext();
                delete currEntry;
                currEntry = nextEntry;
            }
        }
        delete[] table;        
    }

    size_t HashFunc(string word){
        size_t hash = initial;
        for(size_t i = 0; i < word.length(); i++)
        {
            hash = hash ^ (word[i]);
            hash = hash * hashPower;
        }
        return hash%curr_tableSize;
    }

    //reHash function
    void reHash(kData key, vData value) {
        if (growthRatio <= 0.4) {
           return;
        } else {
            for (int i = 0; i < curr_tableSize; i++) {
                if (table[i] = nullptr) {
                    continue;
                } else {
                    for (int j = 0; j < word.length();  j++) {
                        hashNum += hashNum + (int)word[j];
                    }
                    index = HashFunc(word);
                }
            }
        }
    }

    //get data from hash table
    bool contains(const kData &key) {
       int hashValue = HashFunc(key)%curr_tableSize;
       HashNode<kData, vData> *entry = table[hashValue];

       if(entry == nullptr) return false;

       while(entry != nullptr) {
           if (entry->getKey() == key) {
               return true;
           }
           entry = entry->getNext();
       }
       return false;
    }

    vData& get(const kData &key) {
        int hashValue = HashFunc(key);
        HashNode<kData, vData> *entry = table[hashValue%curr_tableSize];

        while(entry != nullptr  && entry->getKey() != key) {
            entry = entry->getNext();
        }
        return entry->getValue();
    }

    //put data into hash table / activate resize function if appropriate
    void put(kData key, vData value) {

        int hash = HashFunc(key) % curr_tableSize;
        if(table[hash] == nullptr) {
            table[hash] = new HashNode<kData, vData>(key, value);
            size++;
        } else {
            HashNode<kData, vData> *entry = table[hash];
            while (entry->getNext() != nullptr) {
                entry = entry->getNext();
            }
            if(entry->getKey() == key) {
                entry->setValue(value);
            } else
                entry->setNext(new HashNode<kData, vData>(key, value));
        }
        if ((size/(double)curr_tableSize) >= 0.4){
            resize();
        }
    }

    //remove data from hash table
    void remove(kData &key) {
        int hashValue = hashFunc(key);
        HashNode<kData, vData> *prev = nullptr;
        HashNode<kData, vData> *entry = table[hashValue%curr_tableSize];

        while(entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }

        if(entry == nullptr) {
            return;
        }
        else {
            if (prev == nullptr) {
                table[hashValue%curr_tableSize] = entry->getNext();
            } else {
                prev ->setNext(entry->getNext());
            }
            delete entry;
        }
    }

    vector<vData> intoVec() {
        vector <vData> keyVec;
        for (int i = 0; i < curr_tableSize; i++) {
            HashNode<kData,vData> * currNode = table[i];
            while (currNode != nullptr) {
                keyVec.push_back(currNode->getValue());
                currNode = currNode->getNext();
            }
        }
        return keyVec;
    }


private:
    int max_tableSize = 169420;
    int init_tableSize = 128;

    int Max_Chains = 20;
    int size;

    HashNode<kData, vData> **table;
    HashNode<kData, vData> **chainLink;

    void resize() {
        int newTableSize = curr_tableSize *2;

        HashNode<kData,vData>** newTable = new HashNode<kData,vData> *[newTableSize];
        for(int i = 0; i < newTableSize; i++){
            newTable[i] = nullptr;
        }
        for (int i = 0; i < curr_tableSize; i++){
            HashNode<kData,vData>* currNode = table[i];
            while(currNode!= nullptr){
                int currNodeHash = HashFunc(currNode->getKey())%newTableSize;
                HashNode<kData,vData>* newLoc = newTable[currNodeHash];
                if(newLoc == nullptr){
                    newTable[currNodeHash] = new HashNode<kData,vData>(currNode->getKey(), currNode->getValue());
                } else{
                    HashNode<kData,vData>* prev;
                    while(newLoc!= nullptr){
                        prev = newLoc;
                        newLoc = newLoc->getNext();
                    }
                    prev->setNext(new HashNode<kData,vData>(currNode->getKey(),currNode->getValue()));
                }
                HashNode<kData,vData>* nextNode = currNode->getNext();
                delete currNode;
                currNode = nextNode;
            }



        }

        delete [] table;
        table = newTable;
        curr_tableSize = newTableSize;
    }
};
#endif // HASHMAP_H
