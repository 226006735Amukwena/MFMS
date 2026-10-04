#ifndef UTILITIES_HEADER_H
#define UTILITIES_HEADER_H

void readLine(const char *msg, char *buffer, int maxLen);
void trimString(char *str);
void readNonEmpty(const char *msg, char *buffer, int maxLen);
int readInt(const char *msg, int minVal, int maxVal);
double readDouble(const char *msg, double minVal, double maxVal);

int equalsIgnoreCase(const char *str1, const char *str2);
int containsIgnoreCase(const char *text, const char *searchTerm);

#endif
