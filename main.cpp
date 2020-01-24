// #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <string.h>
#include <string>
#include "column.h"
#include <ctype.h>
#include <sstream>

// need to trim all strings in tmpTable

enum Type {BOOL, INTEGER, FLOAT, STRING};

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
    // std::cout << str << "\n";
    int maybeInt = std::stoi(str);
    if (maybeInt != 0 && maybeInt != 1) {
        return true;
    }
    return false;
}

// void createColumn(Type colType, std::vector<std::string>* tmpCol, size_t c, Column* table) {
//     if (colType == STRING) {
//         table[c] = new StringColumn(tmpCol->size());
//         for (size_t i = table[c].size; i >= 0; i--) {
//             table[c][i] = tmpCol[i];
//         }
//     }
// }

int main(int argc, char** argv) {

    int flag; // stores current flag from getopt()
    const char* fileName = NULL; // empty string is default if -f flag is missing
    int stringArgExists = 0; // track -f flag count to prevent repeats
    
    while ((flag = getopt(argc, argv, "+f:")) != -1) {
        switch (flag) {
            case 'f':
                if (stringArgExists != 0) {
                    printf("Error: Flags cannot repeat\n");
                    exit(1);
                }
                stringArgExists++;
                fileName = optarg; //optarg created by getopt()
                break;
            case '?':
                if (opterr != 0) {
                    exit(1);
                }
                break;
            default:
                break;
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
 
 
    bool foundStartIndex = false; // has the first index of possible word been seen?
    size_t startIndex = 0; // first index of possible word
 
    size_t maxFields = 0;
    size_t numFields = 0;

    for (size_t i = 0; i < fileSize; i++) {
        if (fileContents[i] == '\n' || i == fileSize - 1) {
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
    for (size_t i = 0; i < fileSize; i++) {        
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


            // // increase capacity of char* for final word by 1
            // if (i == fileSize - 1) {
            //     strLen += 1;
            //     // printf("%c\n", fileContents[i]);
            //     // printf("%zu\n", startIndex);
            //     // printf("%zu\n", strLen);
            // }
            
            // // skip words < 4 letters
            // if (strLen <= 4) {
            //     foundStartIndex = false;
            //     continue;
            // }
 
            // // create String from file contents array
            // char* newStr = new char[strLen + 1];
            // strncpy(newStr, fileContents+startIndex, strLen);
            // newStr[strLen + 1] = 0;
 
            // // convert to lowercase
            // for (size_t i = 0; i < strLen; i++) {
            //     newStr[i] = tolower(newStr[i]);
            // }
 
            // // CountString stores String and Count
            // CountString *str = new CountString(newStr);
            // delete newStr;
 
            // size_t listIndex = list->index_of(str);
            // if (listIndex > list->size()) {
            //     // add to list if new String
            //     list->sorted_add(str);
            // }
            // else {
            //     // remove old String and add with higher count
            //     size_t newCount = list->get(listIndex)->count + 1;
            //     str->count = newCount;
            //     list->remove(listIndex);
            //     list->sorted_add(str);
            // }
            // // reset for next word start index
            // foundStartIndex = false;
    }

    Type colType = BOOL;
    Column* table[maxFields];
    bool foundType = false;
    Type colTypes[maxFields];

    for (size_t c = 0; c < maxFields; c++) {
        if (foundType) {
            colTypes[c] = colType;
            // createColumn(colType, &tmpTable[c], c);
            continue;
        }
        for (size_t r = 0; r < tmpTable[c].size(); r++) {
            std::string currStr = tmpTable[c].at(r);
            if (currStr == "") {
                continue;
            }
            std::cout << currStr << "\n";
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
        // createColumn(colType, &tmpTable[c], c);
        colTypes[c] = colType; 
        foundType = false;
    }

    // for (size_t i = 0; i < maxFields; i++) {
    //     std::cout << colTypes[i] << " ";
    // }

    // std::cout << colTypes[0] << "\n";
    // for (size_t i = 0; i < tmpTable[6].size(); i++) {
    //     std::cout << tmpTable[6].at(i) << "\n";
    // }
    
    // list->printWithCounts();
    // delete fileContents;
    // delete list;
    return 0;
}