#include "sanitizer.h"

Sanitizer::Sanitizer(){
    sanitizeMapFile = "SrcFiles/sanitizeMap.txt";
    stopWordsFile = "SrcFiles/stop.txt";

    loadStopWords();
    loadSanitizeMap();


}
Sanitizer::~Sanitizer(){
    saveStopWords();
    saveSanitizeMap();
}

void Sanitizer::loadStopWords(){
    ifstream stopFileStream;
    stopFileStream.open(stopWordsFile);
    while(stopFileStream.good()){
        string currLine;
        getline(stopFileStream, currLine);
        stopWords.insert(currLine);

    }
    stopFileStream.close();

}

void Sanitizer::saveStopWords(){
    ofstream stopFileStream;
    stopFileStream.open(stopWordsFile);
    auto curr = stopWords.begin();
    curr++;
    while(curr != stopWords.end()){
        stopFileStream << *(curr) << '\n';
        curr++;
    }
    stopFileStream.close();
}

void Sanitizer::saveSanitizeMap(){
    ofstream sanitizeMapStream;
    sanitizeMapStream.open(sanitizeMapFile);
    auto curr = sanitizeMap.begin();
    while(curr != sanitizeMap.end()){
        if(curr->first != ""){
            sanitizeMapStream << curr->first << "|" << curr->second << "\n";
        }
        curr++;
    }
    sanitizeMapStream.close();
}

void Sanitizer::loadSanitizeMap(){
    ifstream sanitizeMapStream;
    sanitizeMapStream.open(sanitizeMapFile);

    while (sanitizeMapStream.good() ) {
        string key;
        string value;
        getline(sanitizeMapStream,key,'|');
        getline(sanitizeMapStream,value);
        if(key != ""){
            sanitizeMap[key] = value;
        }
    }
    sanitizeMapStream.close();


}
bool Sanitizer::sanitize(string & input){
    lowerCase(input);
    if(stopWords.find(input) != stopWords.end()){
        return false;
    }

    stem(input);
    return true;

}

void Sanitizer::stem(string& input){
    string key = input;
    if(sanitizeMap.find(key) == sanitizeMap.end()){
        Porter2Stemmer::stem(input);
        sanitizeMap[key] = input;
    } else {
        input = sanitizeMap[key];
    }

}

void Sanitizer::lowerCase(string& input){
    for(string::size_type i = 0; i < input.length(); i++){
        input[i] = tolower(input[i]);
    }
}
