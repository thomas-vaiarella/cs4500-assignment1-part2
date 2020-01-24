// lang: C++;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <string>
#include <ctype.h>
#include <sstream>

// need to trim all strings in tmpTable

enum Type {BOOL, INTEGER, FLOAT, STRING};

void printEnum(size_t i) {
    if (i == 0) {
        std::cout << "BOOL" << "\n";    
    }
    else if (i == 1) {
        std::cout << "INTEGER" << "\n";
    }
    else if (i == 2) {
        std::cout << "FLOAT" << "\n";
    }
    else {
        std::cout << "STRING" << "\n";
    }
}

bool isCertainlyString(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (isalpha(str.at(i)) || str.at(i) == '\"') {
            return true;
        }
    }
    return false;
}

bool possiblyFloat(std::string str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str.at(i) == '.') {
            return true;
        }
    }
    return false;
}

// fix?
bool possiblyInt(std::string str) {
    int maybeInt = std::stoi(str);
    if (maybeInt != 0 && maybeInt != 1) {
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    
    int flag;
    const char* fileName = NULL; // empty string is default if -f flag is missing
    int fArgExists = 0; // track -f flag count to prevent repeats
    int fromArgExists = 0;
    size_t fromArg;
    int lenArgExists = 0;
    size_t lenArg;
    int commandArgExists = 0; // track number of arguments for commands to print
    int typeArgExists = 0;
    int idxArgExists = 0;
    int missingArgExists = 0;
    size_t typeArg;
    size_t idxArgX;
    size_t idxArgY;
    size_t missingArgX;
    size_t missingArgY;
    
    std::string currArg;

    while ((flag = getopt(argc, argv, "+f:")) != -1) {
        switch (flag) {
            case 'f':
                if (fArgExists != 0) {
                    break;
                }
                fArgExists++;
                fileName = optarg; // optarg created by getopt()
                break;
            default:
                break;
        }
    }

    for (int i=1; i < argc; i++) {
        currArg.clear();
        currArg = std::string(argv[i]);
        
        if (currArg == "-from") {
            if (fromArgExists != 0) {
                    printf("Error: 'from' argument cannot repeat\n");
                    exit(1);
            }
            fromArgExists++;
            fromArg = std::atoi(argv[i + 1]);
        }
        else if (currArg == "-len") {
            if (lenArgExists != 0) {
                    printf("Error: 'len' argument cannot repeat\n");
                    exit(1);
            }
            lenArgExists++;
            lenArg = std::atoi(argv[i + 1]);
        }
        else if (currArg == "-print_col_type") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            commandArgExists++;
            typeArgExists++;
            typeArg = std::atoi(argv[i + 1]);
        }
        else if (currArg == "-print_col_idx") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            commandArgExists++;
            idxArgExists++;
            idxArgX = std::atoi(argv[i + 1]);
            idxArgY = std::atoi(argv[i + 2]);
        }
        else if (currArg == "-is_missing_idx") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            commandArgExists++;
            missingArgExists++;
            missingArgX = std::atoi(argv[i + 1]);
            missingArgY = std::atoi(argv[i + 2]);
        }
    }
 
    if (!fileName) {
        printf("Error: Missing filename argument\n");
        exit(1);
    }

    // open file
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Error: File does not exist\n");
        exit(1);
    }
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
 
    // create char array of file contents
    char* fileContents = new char[fileSize];
    fread(fileContents, 1, fileSize, file);
    fclose(file);

    size_t startOfFile = fromArg;
    if (startOfFile != 0) {
        for (size_t i = fromArg; i < fileSize; i++) {
            if (fileContents[i] == '\n') {
                startOfFile = i + 1;
                break;
            }
        }
    }

    size_t endOfFile = lenArg;
    if (endOfFile >= fileSize) {
        endOfFile = fileSize;
    }
    else {
        for (size_t i = lenArg; i >= startOfFile; i--) {
            if (fileContents[i] == '\n') {
                endOfFile = i;
                break;
            }
        }
    }
 
    bool foundStartIndex = false; // has the first index of possible field been seen?
    size_t startIndex = startOfFile; // first index of possible field
 
    size_t maxFields = 0;
    size_t numFields = 0;

    for (size_t i = startOfFile; i < endOfFile; i++) {
        if (fileContents[i] == '\n' || i == endOfFile - 1) {
            if (fileContents[i] == '>') {
                numFields++;
            }
            if (numFields > maxFields) {
                maxFields = numFields;
            }
            numFields = 0;
            foundStartIndex = false;
        }
        else if (!foundStartIndex && fileContents[i] == '<') {
            foundStartIndex = true;
        }
        else if (foundStartIndex && fileContents[i] == '>') {
            foundStartIndex = false;
            numFields++;
        }
    }
    
    std::vector<std::string> tmpTable[maxFields];
    size_t currCol = 0;

    // parse through file by character
    for (size_t i = startOfFile; i < endOfFile; i++) {
        if (!foundStartIndex && fileContents[i] == '<') {
            foundStartIndex = true;
            startIndex = i + 1;
        }
        else if (foundStartIndex && fileContents[i] == '>') {
            // found a field
            size_t strLen = i - startIndex;
            if (strLen == 0) {
                tmpTable[currCol].push_back("");
            }
            else {
                // create String from file contents array
                char* newStr = new char[strLen + 1];
                strncpy(newStr, fileContents+startIndex, strLen);
                newStr[strLen + 1] = 0;
                tmpTable[currCol].push_back(std::string(newStr));
            }
            foundStartIndex = false;
            currCol++;
        }
        else if (fileContents[i] == '\n') {
            while (currCol < maxFields) {
                tmpTable[currCol].push_back("");
                currCol++;
            }
            currCol = 0;
        }
    }

    Type colType = BOOL;
    bool foundType = false;
    Type colTypes[maxFields];

    for (size_t c = 0; c < maxFields; c++) {
        if (foundType) {
            colTypes[c] = colType;
            continue;
        }
        for (size_t r = 0; r < tmpTable[c].size(); r++) {
            std::string currStr = tmpTable[c].at(r);
            if (currStr == "") {
                continue;
            }
            if (isCertainlyString(currStr)) {
                colType = STRING;
                foundType = true;
                break;
            }
            else if (possiblyFloat(currStr)) {
                colType = FLOAT;
            }
            else if (possiblyInt(currStr) && colType != FLOAT) {
                colType = INTEGER;
            }
        }
        colTypes[c] = colType; 
        foundType = false;
    }

    if (typeArgExists) {
        printEnum(colTypes[typeArg]);
    }
    else if (idxArgExists) {
        std::cout << tmpTable[idxArgX].at(idxArgY) << "\n";
    }
    else {
        if (tmpTable[missingArgX].at(missingArgY) == "") {
            std::cout << "1" << "\n";
        }
        else {
            std::cout << "0" << "\n";
        }
    }

    // deletes?
    return 0;
}