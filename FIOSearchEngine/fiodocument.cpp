#include "FIODocument.h"

FIODocument::FIODocument()
{
    docPath = "";
    wordCount = 0;
}

FIODocument::FIODocument(string path){
    docPath = path;
    wordCount = 0;
}

FIODocument::FIODocument(string path, int initCount){
    docPath = path;
    wordCount = initCount;
}

FIODocument::FIODocument(const FIODocument & cpy){
    docPath = cpy.docPath;
    wordCount = cpy.wordCount;
}

FIODocument& FIODocument::operator =(const FIODocument & cpy){
    docPath = cpy.docPath;
    wordCount = cpy.wordCount;
    return *(this);
}

bool FIODocument::operator ==(const FIODocument& rhs) const {
    return(docPath == rhs.docPath);
}

bool FIODocument::operator <(const FIODocument& rhs) const {

    return docPath.compare(rhs.docPath) < 0 ;
}

string FIODocument::getDocPath(){
    return docPath;
}


