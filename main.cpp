// lang: C++;

// #include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
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

// int flag; // stores current flag from getopt()
//     unsigned long intArg = 0; // 0 is default if -i flag is missing
//     // using const to prevent string literal to char* compiler warning
//     const char* stringArg = ""; // empty string is default if -f flag is missing
//     const char* optionalArg = ""; // empty string is default if optional arg is missing
//     int intArgExists = 0; // track -i flag count to prevent repeats
//     int stringArgExists = 0; // track -f flag count to prevent repeats
    
//     while ((flag = getopt(argc, argv, "+i:f:")) != -1) {
//         switch (flag) {
//             case 'i':
//                 if (intArgExists != 0) {    
//                     printf("Error: Flags cannot repeat\n");
//                     exit(1);
//                 }
//                 intArgExists++;
//                 if (strlen(optarg) > 1 && optarg[0] == '0') {
//                     printf("Error: Flag i does not accept leading 0's\n");
//                     exit(1);
//                 }
//                 // using strtoul instead of atoi to support larger positive integers
//                 char* endptr;
//                 intArg = strtoul(optarg, &endptr, 10);
//                 // checking if input contains only numeric characters
//                 // also prevents negative integers as '-' is non-numeric
//                 for (unsigned long int i = 0; i < strlen(optarg); i++) {
//                     if (isdigit(optarg[i]) == 0) {
//                         printf("Error: Flag i does not accept non-numeric characters\n");
//                         exit(1);
//                     }
//                 }
//                 break;
//             case 'f':
//                 if (stringArgExists != 0) {
//                     printf("Error: Flags cannot repeat\n");
//                     exit(1);
//                 }
//                 stringArgExists++;
//                 stringArg = optarg;
//                 break;
//             case '?':
//                 if (opterr != 0) {
//                     exit(1);
//                 }
//                 break;
//             default:
//                 break;
//         }
//     }

int main(int argc, char** argv) {
    
    const char* fileName = NULL; // empty string is default if -f flag is missing
    int fArgExists = 0; // track -f flag count to prevent repeats
    int fromArgExists = 0;
    size_t fromArg;
    int lenArgExists = 0;
    size_t lenArg;
    int commandArgExists = 0; // track number of arguments for commands to print
    
    std::string currArg;
    
    for (int i=1; i < argc; i++) {
        currArg.clear();
        currArg = std::string(argv[i]);
        
        if (currArg == "-f") {
            if (fArgExists != 0) {
                printf("Error: Flags cannot repeat\n");
                exit(1);
            }
            fArgExists++;
            if (i++ < argc) {
                std::string file(argv[i++]);
                fileName = file.c_str();
                std::cout << "Filename = " << fileName << "\n";
            }
        }
        
        else if (currArg == "-from") {
            if (fromArgExists != 0) {
                    printf("Error: 'from' argument cannot repeat\n");
                    exit(1);
                }
                fromArgExists++;
                if (i++ < argc) {
                    fromArg = std::atoi(argv[i++]);
                    std::cout << "From = " << fromArg << "\n";
                }
        }
        else if (currArg == "-len") {
            if (lenArgExists != 0) {
                    printf("Error: 'len' argument cannot repeat\n");
                    exit(1);
            }
            lenArgExists++;
            if (i++ < argc) {
                lenArg = std::atoi(argv[i++]);
                std::cout << "Length = " << lenArg << "\n";
            }
        }
        else if (currArg == "-print_col_type") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            lenArgExists++;
            if (i++ < argc) {
                //fill in 1 variable here
            }
        }
        else if (currArg == "-print_col_idx") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            lenArgExists++;
            if (i++ < argc && i+2 < argc) {
                //fill in 2 other variables here
            }
        }
        else if (currArg == "-is_missing_idx") {
            if (commandArgExists != 0) {
                    printf("Error: cannot have more than one command to print\n");
                    exit(1);
            }
            lenArgExists++;
            if (i++ < argc && i+2 < argc) {
                //fill in 2 other variables here
            }
        }
    }
    
//    while ((flag = getopt(argc, argv, "+f:")) != -1) {
//        switch (flag) {
//            case 'f':
//                if (stringArgExists != 0) {
//                    printf("Error: Flags cannot repeat\n");
//                    exit(1);
//                }
//                stringArgExists++;
//                fileName = optarg; //optarg created by getopt()
//                break;
//            case '?':
//                if (opterr != 0) {
//                    exit(1);
//                }
//                break;
//            default:
//                break;
//        }
//    }
 
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

    startOfFile = fromArg;
    if (startOfFile != 0) {
        for (size_t i = fromArg; i < fileSize; i++) {
            if (fileContents[i] == '\n') {
                startOfFile = i + 1;
                break;
            }
        }
    }

    endOfFile = lenArg
    if (endOfFile != fileSize) {
        for (size_t i = lenArg; i >= startOfFile; i--) {
            if (fileContents[i] == '\n') {
                endOfFile = i;
                break;
            }
        }
    }
 
    // create char array of file contents
    char* fileContents = new char[fileSize];
    fread(fileContents, 1, fileSize, file);
    fclose(file);

 
    bool foundStartIndex = false; // has the first index of possible word been seen?
    size_t startIndex = 0; // first index of possible word
 
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
                strncpy(newStr, fileContents+startOfFile+startIndex, strLen);
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

        for (size_t r = 0; r < tmpTable[0].size(); r++) {
            for (size_t c = 0; c < maxFields; c++) {
                std::cout << tmpTable[r].at(c) << " "; 
            }
            std::cout << "\n";
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

    for (size_t i = 0; i < maxFields; i++) {
        std::cout << colTypes[i] << " ";
    }

    // std::cout << colTypes[0] << "\n";
    // for (size_t i = 0; i < tmpTable[6].size(); i++) {
    //     std::cout << tmpTable[6].at(i) << "\n";
    // }
    
    // list->printWithCounts();
    // delete fileContents;
    // delete list;
    return 0;
}