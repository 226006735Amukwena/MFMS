#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include <stddef.h>

void readLine(const char *msg, char *buffer, int maxLen) 
{
    size_t length;
    int ch;

    printf("%s", msg);
    
    if (!fgets(buffer, maxLen, stdin)) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    
    length = strlen(buffer);
    
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0'; 
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
}

void trimString(char *str)
{
    size_t strLen = strlen(str);
    size_t beginIdx = 0;

    while (strLen > 0 && isspace((unsigned char)str[strLen - 1])) {
        str[--strLen] = '\0';
    }
    
    while (str[beginIdx] != '\0' && isspace((unsigned char)str[beginIdx])) {
        beginIdx++;
    }

    if (beginIdx > 0) {
        memmove(str, str + beginIdx, strLen - beginIdx + 1);
    }
}

void readNonEmpty(const char *msg, char *buffer, int maxLen)
{
    while (1) {
        readLine(msg, buffer, maxLen);
        trimString(buffer);
        
        if (strlen(buffer) > 0) {
            return;
        }
        
        printf("Input cannot be empty. Please try again.\n");
    }
}

int readInt(const char *msg, int minVal, int maxVal)
{
    char inputBuffer[64];
    char *endPtr;
    long parsedVal;

    while (1) {
        readLine(msg, inputBuffer, sizeof(inputBuffer));
        trimString(inputBuffer);
        
        if (inputBuffer[0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        
        parsedVal = strtol(inputBuffer, &endPtr, 10);
        
        if (*endPtr != '\0') {
            printf("Invalid input. Please enter a valid whole number.\n");
        } else if (parsedVal < minVal || parsedVal > maxVal) {
            printf("Input out of range. Please enter a number between %d and %d.\n", minVal, maxVal);
        } else {
            return (int)parsedVal;
        }
    }
}

double readDouble(const char *msg, double minVal, double maxVal)
{
    char inputBuffer[64];
    char *endPtr;
    double parsedVal;

    while (1) {
        readLine(msg, inputBuffer, sizeof(inputBuffer));
        trimString(inputBuffer);
        
        if (inputBuffer[0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        
        parsedVal = strtod(inputBuffer, &endPtr);
        
        if (*endPtr != '\0') {
            printf("Invalid input. Please enter a valid number.\n");
        } else if (parsedVal < minVal || parsedVal > maxVal) {
            printf("Input out of range. Please enter a number between %.2f and %.2f.\n", minVal, maxVal);
        } else {
            return parsedVal;
        }
    }
}

static void lowerCopy(char *target, const char *source, size_t maxBytes)
{
    size_t idx;
    
    for (idx = 0; idx < maxBytes - 1 && source[idx] != '\0'; idx++) {
        target[idx] = (char)tolower((unsigned char)source[idx]);
    }
    
    target[idx] = '\0';
}   

int equalsIgnoreCase(const char *str1, const char *str2)
{
    char buf1[256];
    char buf2[256];

    lowerCopy(buf1, str1, sizeof(buf1));
    lowerCopy(buf2, str2, sizeof(buf2));

    return strcmp(buf1, buf2) == 0;
}

int containsIgnoreCase(const char *text, const char *searchTerm)
{
    char textBuf[256];
    char searchBuf[256];

    lowerCopy(textBuf, text, sizeof(textBuf));
    lowerCopy(searchBuf, searchTerm, sizeof(searchBuf));
    
    return strstr(textBuf, searchBuf) != NULL;
}
