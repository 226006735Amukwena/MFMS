#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void readLine(const char *prompt, char *buf, int size) 
  {
      size_t len;
      int c;

     printf("%s", prompt);
      if (fgets(buf, size, stdin) == NULL) {
          printf("\nInput closed. Exiting.\n");
          exit(0);
      }
       len = strlen(buf);
      if (len > 0 && buf[len - 1] == '\n') {
          buf[len - 1] = '\0'; 
      } else {
        while ((c = getchar()) != '\n' && c != EOF) { }
      }
    }

void trimString(char *s)
{
    size_t len = strlen(s);
    size_t start = 0;

    while (len> 0 && isspace ((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }

    if (start > 0) {
        memmove(s, s + start, len - start + 1);
    }
}

void readNonEmpty(const char *prompt, char *buf, int size)
{
    for (;;) {
        readLine(prompt, buf, size);
        trimString(buf);
        if (strlen(buf) > 0) {
            return;
        }
        printf("Input cannot be empty. Please try again.\n");
    }
}

int readInt(const char *prompt, int min, int max)
   {
    char buf[64];
    char *end;
    long value;

    for(;;) {
        readLine(prompt, buf, sizeof(buf));
        trimString(buf);
        if (buf [0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        value = strtol(buf, &end, 10);
        if (*end != '\0') {
            printf("Invalid input. Please enter a valid whole number.\n", buf);
        }else if (value < min || value > max) {
            printf("Input out of range. Please enter a number between %d and %d.\n", min, max);
        } else {
            return (int)value;
        }

    }

}

double readDouble(const char *prompt, double min)
{
    char buf[64];
    char *end;
    double value;

    for(;;) {
        readLine(prompt, buf, sizeof(buf));
        trimString(buf);
        if (buf[0] == '\0') {
            printf("Input cannot be empty. Please try again.\n");
            continue;
        }
        value = strtod(buf, &end);
        if (*end != '\0') {
            printf("Invalid input. Please enter a valid number.\n");
        } else if (value < min) {
            printf("Input out of range. Please enter a number greater than or equal to %.2f.\n", min);
        } else {
            return value;
        }
    }
} 

static void lowerCopy(char *dst, const char *src, size_t size)

{
size_t i;
for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
    dst[i] = (char)tolower((unsigned char)src[i]);
    }
dst[i] = '\0';
}   

int equalsIgnoreCase(const char *a, const char *b)
{
    char lowerA[256];
    char lowerB[256];

    lowerCopy(lowerA, a, sizeof(lowerA));
    lowerCopy(lowerB, b, sizeof(lowerB));

    return strcmp(lowerA, lowerB) == 0;
}

int containsIgnoreCase(const char *haystack, const char *needle)
{
    char lowerHaystack[256];
    char lowerNeedle[256];

    lowerCopy(lowerHaystack, haystack, sizeof(lowerHaystack));
    lowerCopy(lowerNeedle, needle, sizeof(lowerNeedle));
    return strstr(lowerHaystack, lowerNeedle) != NULL;
}
