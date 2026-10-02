#ifndef UTIL_H
#define UTIL_H

void    readLine(const char *prompt, char *buf, int size);
void    trimString(char *s);
void    readNonEmpty(const char *promt, char *buf, int size);
int     readInt(const char *prompt, int min, int max);
double  readDouble(const char *prompt, double min, double max);

int     equalsIgnoreCase(const char *a, const char *b);
int     containsIgnoreCase(const char *haystack, const char * needle);
#endif 