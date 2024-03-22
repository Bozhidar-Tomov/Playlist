#pragma once
#include <ostream>

void myStrCpy(char *, const char *);
void myStrCpy(unsigned char *, const unsigned char *);
int myStrLen(const char *);
void resize(char *&, const int);
int myStrCmp(const char *, const char *);
int strToInt(const char *);
void printStr(const char *, std::ostream &);
void mySetW(const int, const char, std::ostream &);
void removeExtraSpaces(char *);
void myStrcat(char *, const char *);
int last1BitPos(unsigned char);