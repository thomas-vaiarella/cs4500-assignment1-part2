#include "list.h"
#include "object.h"
#include "string.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
                fileName = optarg;
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
    // fileContents[fileSize] = 0;

    bool foundStartIndex = 0; // has the first index of possible word been seen
    size_t startIndex = 0; // first index of possible word
    SortedStrList *list = new SortedStrList();

    // parse through file by character
    for (size_t i = 0; i < fileSize; i++) {
        int isAlpha = isalpha(fileContents[i]);
        
        if (!foundStartIndex && isAlpha) {
            foundStartIndex = true;
            startIndex = i;
        }
        else if (foundStartIndex && (!isAlpha || i == fileSize - 1)) {
            // found a word
            size_t strLen = i - startIndex;

            // increase capacity of char* for final word by 1
            if (i == fileSize - 1) {
                strLen += 1;
                // printf("%c\n", fileContents[i]);
                // printf("%zu\n", startIndex);
                // printf("%zu\n", strLen);
            }
            
            // skip words < 4 letters
            if (strLen <= 4) {
                foundStartIndex = false;
                continue;
            }

            // create String from file contents array
            char* newStr = new char[strLen + 1];
            strncpy(newStr, fileContents+startIndex, strLen);
            newStr[strLen + 1] = 0;

            // convert to lowercase
            for (size_t i = 0; i < strLen; i++) {
                newStr[i] = tolower(newStr[i]);
            }

            // CountString stores String and Count
            CountString *str = new CountString(newStr);
            delete newStr;

            size_t listIndex = list->index_of(str);
            if (listIndex > list->size()) {
                // add to list if new String
                list->sorted_add(str);
            }
            else {
                // remove old String and add with higher count
                size_t newCount = list->get(listIndex)->count + 1;
                str->count = newCount;
                list->remove(listIndex);
                list->sorted_add(str);
            }
            // reset for next word start index
            foundStartIndex = false;
        }
    }
    list->printWithCounts();
    delete fileContents;
    delete list;
    return 0;
}