#include "documentparse.h"

DocumentParse::DocumentParse()
{

}

void DocumentParse::select_initial_Dir(const char* dir) {
    initial_Directory = dir;
}

void DocumentParse::accessFiles(const char* dir) {
    this->select_initial_Dir(dir);
    struct dirent *dir_struct;
    DIR *d;
    d = opendir(dir);
    if (d == NULL) {
        cout << "ERROR: Invalid directory" << endl;
        exit(1);
    }
    while ((dir_struct = readdir(d)) != NULL) {
        if(dir_struct->d_name[0] == '.')
            continue;
        case_Names.push_back(string(dir_struct->d_name));
    } closedir(d);
}

//analyze ascii values to determine whether to ignore or not
bool isChar(char thing) {
    if (thing >= 65 && thing <= 90) {
        return true;
    }
    if (thing >= 97 && thing <= 122) {
        return true;
    } else {
        return false;
    }
}

void DocumentParse::inputIntoIndex(Index* indexPtr, Sanitizer* sanitizer){
    string dir = initial_Directory;
    dir+="/";
    for(unsigned index = 0; index < case_Names.size();index++){

        FIODocument currDoc(dir+ case_Names[index]);
        if(!(indexPtr->hasDocBenParsed(currDoc))){
            map<string, int> currData = read_through((dir + case_Names[index]).c_str(), sanitizer);
            int wordCount = 0;
            for(auto entryIter = currData.begin(); entryIter != currData.end(); entryIter++){
                wordCount += entryIter->second;
            }
            currDoc.increaseWordCount(wordCount);

            for(auto entryIter = currData.begin(); entryIter !=currData.end(); entryIter++){
                IndexEntry currIndex(entryIter-> first);
                currIndex.addDocs(currDoc, entryIter->second);
                indexPtr->addEntry(currIndex);

            }
            indexPtr->addParseDoc(currDoc);
            indexPtr->incrementDocumentCount();
            indexPtr->incrementTotalWordCount(wordCount);

        }
  }

}


map<string, int> DocumentParse::read_through(string inputStream, Sanitizer* sanitizer) {
    ifstream input;
    map<string, int> output;
    input.open(inputStream);
    string curr_line;
    string currWord = "";
    vector<string> wordStream;
    for (unsigned lineNo = 0; lineNo < inputStream.length(); lineNo ++) {
        getline(input, curr_line);
        wordStream.push_back(curr_line);

        for (unsigned i = 0; i < wordStream[lineNo].length() && wordStream[lineNo][i] != '\0'; i ++) {
            //cout << wordStream[lineNo][i] << endl;;
            if (isChar(wordStream[lineNo][i])) {

                currWord+= wordStream[lineNo][i];
            }
            if(!isChar(wordStream[lineNo][i])){
                    if(sanitizer->sanitize(currWord)){
                       if(output.find(currWord) == output.end()){
                            output.insert(pair<string, int>(currWord,0));
                       }
                        output[currWord]++;
                    }
                    currWord = "";
                    continue;
                }
            }
    }
    input.close();
    return output;
}

DocumentParse::~DocumentParse()
{

}
