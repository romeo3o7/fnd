#ifndef FILE_H
#define FILE_H
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int cacheCount();
char * concatStrings(const char *s1 , const char *s2);
int writeValue(int fd , char buffer , unsigned int size , char *values);
int createDirctory(const char *s);
char * concatStrings(const char *s1 , const char *s2);
#endif
