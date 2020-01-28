#include "searchengine.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;


SearchEngine::SearchEngine(){
    sanitizer = new Sanitizer();
    index = new HashIndex();
    index->setPersistentPath("./SrcFiles/PersistentIndex.txt");
    index->addSanitizer(sanitizer);

    parser = new DocumentParse();
}

SearchEngine::~SearchEngine(){
    delete sanitizer;
    delete index;
    delete parser;
}

void SearchEngine::speedTest(string pathToFolder, string searchWord){

    //1. Have parser load the path into the Index

    cout << "Parsing all documents" << endl;

    parser->select_initial_Dir(pathToFolder.c_str());

    parser->accessFiles(pathToFolder.c_str());

    parser->inputIntoIndex(index, sanitizer);




    map<FIODocument,int> searchResult;
    //2. get the searchWord
    if(index->contains(searchWord)){

        IndexEntry searchEntry = index->get(searchWord);

        searchResult= searchEntry.getDocs();

    }
    int size = 0;
    for(auto iter = searchResult.begin(); iter != searchResult.end(); iter++){
        size++;
    }
    //3. Output relevant data
    cout << "Total Documents Parsed: " << index->getDocumentCount() << endl
         << "Unique Word Count: " << index->getWordCount() << endl
         << searchWord << " appears " << size << " times." << endl;

    index->saveIndex();
}

void SearchEngine::startUI(){
    cout << "Welcome to the FIO search engine" << endl;

    displayBaseMenu();

    char input;
    cin >> input;
    while(input != 'Q'){
        switch(input){
            case 'M':
                maintenance();
                break;
            case 'S':
                statistics();
                break;
            case 'E':
                search();
                break;
            case 'Q':
                break;
            default:
                break;
        }

        displayBaseMenu();
        cin.clear();
        cin >> input;

    }
    index->saveIndex();
}

void SearchEngine::displayBaseMenu(){
    cout << "Press M for maintenance" << endl
         << "Press S for statistics" << endl
         << "Press E for searching" << endl
         << "Press Q to quit" << endl
         << "COMMAND: ";
}

void SearchEngine::maintenance(){
    string currInput = "";
    cin.clear();
    cin.ignore();
    do{
        maintenanceMenu();
        getline(cin,currInput);
        if(currInput.compare("ADD") == 0){
            addIndex();
        } else if (currInput.compare("CLEAR") == 0){
            delete index;
            index = new IndexAvlTree();
        } else if(currInput.compare("NORM") == 0){
            index->loadIndex();
        } else if(currInput.compare("AVL") == 0){
            vector<IndexEntry> entries = index->getDataAsVector();
            Index* newIndex = new IndexAvlTree();
            for(auto entryIter = entries.begin(); entryIter != entries.end(); entryIter++){
                map<FIODocument, int> entryDocs = entryIter->getDocs();
                for(auto entryDocIter = entryDocs.begin(); entryDocIter != entryDocs.end(); entryDocIter++){
                    FIODocument doc(entryDocIter->first);
                    if(!(newIndex->hasDocBenParsed(doc))){
                        newIndex->addParseDoc(doc);
                        newIndex->incrementDocumentCount();
                    }
                    newIndex->incrementTotalWordCount(entryDocIter->second);
                }

                newIndex->addEntry(*entryIter);
            }

            delete index;
            index = newIndex;
            index->addSanitizer(sanitizer);



        } else if(currInput.compare("HASH") == 0){
            vector<IndexEntry> entries = index->getDataAsVector();
            Index* newIndex = new HashIndex();
            for(auto entryIter = entries.begin(); entryIter != entries.end(); entryIter++){
                map<FIODocument, int> entryDocs = entryIter->getDocs();
                for(auto entryDocIter = entryDocs.begin(); entryDocIter != entryDocs.end(); entryDocIter++){
                    FIODocument doc(entryDocIter->first);
                    if(!(newIndex->hasDocBenParsed(doc))){
                        newIndex->addParseDoc(doc);
                        newIndex->incrementDocumentCount();
                    }
                    newIndex->incrementTotalWordCount(entryDocIter->second);
                }

                newIndex->addEntry(*entryIter);
            }

            delete index;
            index = newIndex;
            index->addSanitizer(sanitizer);

        }
    }while(currInput.compare("BACK") != 0);
}

void SearchEngine::maintenanceMenu(){
    cout << "Type ADD to add to the index" << endl
         << "Type CLEAR to clear the index" << endl
         << "Type NORM to load the default index" << endl
         << "Type AVL to load a AVLIndex" << endl
         << "Type HASH to load a hashIndex" << endl
         << "Type BACK to go back" << endl
         << "COMMAND: ";
}

void SearchEngine::addIndex(){
    cout << "Path to docs to add" << endl;
    string path = "";
    getline(cin, path);
    parser->select_initial_Dir(path.c_str());
    parser->accessFiles(path.c_str());
    parser->inputIntoIndex(index,sanitizer);
    cout << "Added " << path << " to index" << endl;
}

void SearchEngine::statistics(){
    string currInput = "";
    cin.clear();
    cin.ignore();
    do{
        statisticsMenu();
        getline(cin,currInput);

        if(currInput.compare("OPINIONS") == 0){
            cout << index->getDocumentCount() << " Have been indexed" << endl;
        } else if(currInput.compare("AVERAGE") == 0){
            cout << (index->getTotalWordCount())/(index->getDocumentCount()) << " is average words per opinion" << endl;
        } else if(currInput.compare("TOP") == 0) {
            vector<pair<string, int>> top50 = index->getTop50Words();
            for(auto topIter = top50.begin(); topIter != top50.end(); topIter++){
                cout << topIter->first << " appears " << topIter->second << " times" <<endl;
            }
        }
    }while(currInput.compare("BACK") !=0);

}

void SearchEngine::statisticsMenu(){
    cout << "Type OPINIONS for number of opinions" << endl
         << "Type AVERAGE for number of words per opinion" << endl
         << "Type TOP for the list of the top 50 words" << endl
         << "Type BACK to go back" << endl
         << "COMMAND: ";
}


void SearchEngine::search(){
    cin.ignore();
    string input;
    searchMenu();
    getline(cin,input);
    while(input.compare("BACK") != 0){
        if(input.compare("NORM") == 0){
            index->loadIndex();
        } else if(input.compare("SEARCH") == 0){
            while(input.compare("!") != 0){
                cout << "Enter search query (type HELP FOR ASSISTANCE)" << endl;
                getline(cin,input);
                if(input.compare("HELP") == 0){

                } else if(input.compare("!") != 0){
                   getSearchResult(input);
                }
            }
        }
        searchMenu();
        getline(cin,input);
    }
}

void SearchEngine::searchMenu(){
    cout << "type NORM for using the default index" << endl
         << "type SEARCH to use the currently loaded index" << endl
         << "type BACK to go back to the main menu" << endl
         << "COMMAND: ";
}


void SearchEngine::getSearchResult(string searchQuery){
    vector<string> searchResults;
    string currentResult;
    for(unsigned index = 0; index < searchQuery.size(); index++){
        if(searchQuery.at(index) == ' '){
            searchResults.push_back(currentResult);
            currentResult = "";
        } else{
            currentResult+= searchQuery.at(index);
        }
    }
    searchResults.push_back(currentResult);
    map<FIODocument, int> searchMap;
    bool intersectionMode = false;
    bool unionMode = false;
    bool differenceMode =false;
    for(auto currSearch = searchResults.begin(); currSearch != searchResults.end(); currSearch++){
        if((*(currSearch)).compare("AND") == 0){
            intersectionMode = true;
            differenceMode = false;
            unionMode = false;
        } else if( (*(currSearch)).compare("OR") == 0){
            unionMode = true;
            differenceMode = false;
            intersectionMode = false;
        } else if( (*(currSearch)).compare("NOT") == 0){
            differenceMode = true;
            unionMode = false;
            intersectionMode = false;
        }else if(index->contains(*(currSearch))){
            if(searchMap.size() == 0 && !differenceMode){
                searchMap = index->get(*(currSearch)).getDocs();
            } else{
                if(intersectionMode){
                    map<FIODocument,int> currEntryMap = index->get(*(currSearch)).getDocs();
                    map<FIODocument,int> finalEntryMap;
                    for(auto iter = currEntryMap.begin(); iter != currEntryMap.end(); iter++){
                        if(searchMap.find(iter->first) != searchMap.end()){
                            finalEntryMap.insert(pair<FIODocument,int>(iter->first, (iter->second + searchMap.find(iter->first)->second)));
                        }
                    }
                    searchMap = finalEntryMap;
                } else if(unionMode){
                    map<FIODocument, int> currEntryMap = index->get(*(currSearch)).getDocs();
                    for(auto iter = currEntryMap.begin(); iter!= currEntryMap.end(); iter++){
                        if(searchMap.find(iter->first) == searchMap.end()){
                            searchMap.emplace(pair<FIODocument,int>(iter->first, iter->second));
                        } else{
                            searchMap.at(iter->first) += iter->second;
                        }
                    }
                } else if(differenceMode){
                    map<FIODocument, int> currEntryMap = index->get(*(currSearch)).getDocs();
                    for(auto iter = currEntryMap.begin(); iter!= currEntryMap.end(); iter++){
                        if(searchMap.find(iter->first) != searchMap.end()){
                            searchMap.erase(iter->first);
                        }
                    }
                }
            }

        }
    }

    vector<pair<FIODocument,double>> sortedSearchResult = castToVector(searchMap);
    int sizect = 0;
    string currCommand = "";
    int currentPage = 0;
    do{
        int cnt = 0;
        for(unsigned index = currentPage*25; index < sortedSearchResult.size() && cnt!= 25 ; index++){
            cout << index << ". ";
            displayIndividualSearchResult(sortedSearchResult.at(index).first.getDocPath());
            cout << endl;
            cnt++;
        }
        searchResponse();
        getline(cin, currCommand);
        if(currCommand.compare("Next") == 0 && ((unsigned)sizect*25) < sortedSearchResult.size()){
            currentPage++;

        } else if(currCommand.compare("Back") == 0 && sizect>0){
            currentPage--;
        } else if(currCommand.find_first_not_of( "0123456789" ) == string::npos && (stoi(currCommand) >= currentPage * 25 && stoi(currCommand) < (currentPage+1) *25)){
            cout << "Displaying " << sortedSearchResult.at(stoi(currCommand)).first.getDocPath() << endl;
            displayDoc(sortedSearchResult.at(stoi(currCommand)).first.getDocPath());
            cout << endl;
        }

    } while (currCommand.compare("Quit")!=0);

}
bool SearchEngine::isChar(char thing) {
    if (thing >= 65 && thing <= 90) {
        return true;
    }
    if (thing >= 97 && thing <= 122) {
        return true;
    } else {
        return false;
    }
}
void SearchEngine::displayDoc(string path){
    FILE* fp = fopen(path.c_str(), "r");

    char buffer[65536];
    FileReadStream is(fp, buffer, sizeof(buffer));

    Document d;
    d.ParseStream(is);
    string docTxt = d["plain_text"].GetString();
    int wordCount = 0;
    bool inWord = false;
    for(unsigned index = 0; index < docTxt.size() && wordCount < 300; index++){
        cout << docTxt[index];
        if(inWord && !isChar(docTxt[index])){
            wordCount++;
            inWord = false;
        } else if(isChar(docTxt[index])){
            inWord = true;
        }
    }
    cout << endl;
    fclose(fp);
}
void SearchEngine::searchResponse(){
    cout << "Enter document # to pull it up" << endl
         << "Enter Next for next page" << endl
         << "Enter Back for last page" << endl
         << "Enter Quit to leave" << endl;
}

bool comparison(pair<FIODocument,double> lhs, pair<FIODocument,double> rhs){
    return lhs.second > rhs.second;
}

vector<pair<FIODocument, double>> SearchEngine::castToVector(map<FIODocument, int> inputMap){
    vector<pair<FIODocument, double>> output;
    for(auto inputIter = inputMap.begin(); inputIter != inputMap.end(); inputIter++){
        FIODocument currDoc = inputIter->first;
        double relevancyValue = (double)inputIter->second/(double)currDoc.getWordCount() * log((double)index->getDocs().size()/(double)inputMap.size());
        output.push_back(pair<FIODocument,double>(currDoc, relevancyValue));
    }
    sort(output.begin(), output.end(), comparison);
    return output;
}

void SearchEngine::displayIndividualSearchResult(string currSearch){
    FILE* fp = fopen(currSearch.c_str(), "r");

    char buffer[65536];
    FileReadStream is(fp, buffer, sizeof(buffer));

    Document d;
    d.ParseStream(is);
    string opinion= d["absolute_url"].GetString();
    auto iter = opinion.rbegin();
    if(d.HasMember("absolute_url") && d["absolute_url"].IsString()){

        for(iter++ ; *(iter) != '/'; iter++);
    }
    iter--;
    while(*iter!= '/'){
        cout <<*iter;
        iter--;
    }

    fclose(fp);
}

void SearchEngine::experiment(){


    ofstream of;

    Index * hashIndex10 = new HashIndex();
    hashIndex10->addSanitizer(sanitizer);
    parser->select_initial_Dir("SrcFiles/10Docs");
    parser->accessFiles("SrcFiles/10Docs");
    parser->inputIntoIndex(hashIndex10,sanitizer);

    Index * hashIndex100 = new HashIndex();
    hashIndex100->addSanitizer(sanitizer);

    parser->select_initial_Dir("SrcFiles/100Docs");
    parser->accessFiles("SrcFiles/100Docs");
    parser->inputIntoIndex(hashIndex100,sanitizer);

    Index * hashIndex1000 = new HashIndex();
    hashIndex1000->addSanitizer(sanitizer);
    parser->select_initial_Dir("SrcFiles/1000Docs");
    parser->accessFiles("SrcFiles/1000Docs");
    parser->inputIntoIndex(hashIndex1000,sanitizer);

    Index * avlIndex10 = new IndexAvlTree();
    avlIndex10->addSanitizer(sanitizer);
    parser->select_initial_Dir("SrcFiles/10Docs");
    parser->accessFiles("SrcFiles/10Docs");
    parser->inputIntoIndex(avlIndex10,sanitizer);

    Index * avlIndex100 = new IndexAvlTree();
    avlIndex100->addSanitizer(sanitizer);
    parser->select_initial_Dir("SrcFiles/100Docs");
    parser->accessFiles("SrcFiles/100Docs");
    parser->inputIntoIndex(avlIndex100,sanitizer);

    Index * avlIndex1000 = new IndexAvlTree();
    avlIndex100->addSanitizer(sanitizer);
    parser->select_initial_Dir("SrcFiles/1000Docs");
    parser->accessFiles("SrcFiles/1000Docs");
    parser->inputIntoIndex(avlIndex1000,sanitizer);


    vector<string> searchQueries;
    searchQueries.push_back("law");
    searchQueries.push_back("murder");
    searchQueries.push_back("thought");
    searchQueries.push_back("total");
    searchQueries.push_back("defendant");
    searchQueries.push_back("frequent");
    searchQueries.push_back("Kansas");
    searchQueries.push_back("settled");
    searchQueries.push_back("list");
    searchQueries.push_back("vote");

    of.open("AVLSearching.csv");
    of << "10";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            avlIndex10->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;

    of << "100";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            avlIndex100->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;

    of << "1000";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            avlIndex1000->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;
    of.close();
    of.open("HashSearching.csv");
    of << "10";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            hashIndex10->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;

    of << "100";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            hashIndex100->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;

    of << "1000";
    for(int cnt = 0; cnt < 3; cnt++){
        of << ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        for(auto iter = searchQueries.begin(); iter != searchQueries.end();iter++){
            hashIndex1000->contains(*iter);
        }

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;
    }
    of << endl;
    of.close();


    of.open("AVLIterating.csv");
    of << "10";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        avlIndex10->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;

    of << "100";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        avlIndex100->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;

    of << "1000";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        avlIndex1000->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;

    of.close();

    of.open("HashIterating");
    of << "10";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        hashIndex10->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;

    of << "100";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        hashIndex100->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;

    of << "1000";
    for(int cnt = 0; cnt <3; cnt++){
        of<< ",";
        high_resolution_clock::time_point start = high_resolution_clock::now();

        hashIndex1000->getDataAsVector();

        high_resolution_clock::time_point end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end -start).count();
        of << duration;

    }
    of<< endl;
    of.close();
}
