#ifndef CHILD_H
#define CHILD_H
#include <fcntl.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int task(char*path,char *argument[]);
int silentTask(char *path, char *args[]);
#endif
