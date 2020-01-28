//This file contains the memory mapping protocol
//Written by Alexander Clark

#include "mmaping.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

size_t fileSize(const char* fileName){
    struct stat sb;
    stat(fileName, &sb);
    return sb.st_size;
}

char* parsing::openDoc(string docPath){
    struct stat sb;

    int fd = open(docPath.c_str(), O_RDONLY, 0);

    size_t filesize = fileSize(docPath.c_str());

    void* file = mmap(NULL,filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);

    return (char*) file;
}
void parse(int argc, char *argv[]){

    struct stat sb;

    //file descriptor: checks if the file can be opened
    int fd = open(argv[1], O_RDONLY, 0);

    //file size: checks the size of the file
    size_t filesize = fileSize(argv[1]);

    //pointer to file in memory
    void* file_in_memory = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);

    //casting pointer to file stored in memory
    char* data = (char*) file_in_memory;


        if (fstat(fd, &sb) == -1){
            perror("couldn't get file size. \n");
        }
        else{
           printf("file size is %ld\n", filesize);

        printf("Printing file as an array of characters...\n\n");
        for (int i = 0; i < filesize; i++){
            printf("%c", data[i]);
        }
        printf("\n");

        munmap(file_in_memory, filesize);
        close(fd);
    }
    return;
}

int countWords(int wordFreq, string wordStr) {
    wordFreq = 0;
    while (wordFreq <= wordStr.length()) {
        ++wordFreq;
    }
    return wordFreq;
}


