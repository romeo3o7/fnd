#ifndef PACKAGE_H
#define PACKAGE_H
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "../include/child.h"
#include <unistd.h>
#include <stdbool.h>

typedef struct {
    char *flag;
    char *path;
    char *args[6];
} operations;

int packageAnalysis(const char* flag, char *package);
bool checkInstalled(char *package);
#endif
