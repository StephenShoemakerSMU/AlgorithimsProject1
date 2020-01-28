#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "string"
#include "searchengine.h"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc ==1){
        //Catch::Session().run(argc, argv);
        SearchEngine searchEngine;
        searchEngine.experiment();
    }

    if(argc == 2){
        SearchEngine searchEngine;
        searchEngine.startUI();
    }

    if(argc == 3){
        SearchEngine searchEngine;
        searchEngine.speedTest(argv[1], argv[2]);
    }


    return 0;
}
