//Figure It Out Hash Node Implementation
//This was written by Alexander Clark

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>

using namespace std;

template <typename kData, typename vData>
class HashNode {
public:
    HashNode(const kData &key, const vData &value) :
        key(key), value(value), next(nullptr) {

    }

    kData getKey() const {
        return key;
    }

    HashNode *getNext() const {
        return next;
    }

    vData& getValue() {
        return value;
    }

    void setNext(HashNode *next) {
        this->next = next;
    }

    void setValue(vData value) {
        this->value = value;
    }

private:
    kData key;
    vData value;
    HashNode *next;
    HashNode* entry;
};


#endif // HASHTABLE_H
