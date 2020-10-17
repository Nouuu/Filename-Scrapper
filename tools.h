//
// Created by Unknow on 17/10/2020.
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

#ifndef WIN32
#include <sys/types.h>
#endif

#ifndef FILENAME_SCRAPPER_STRTOOLS_H
#define FILENAME_SCRAPPER_STRTOOLS_H

typedef struct {
    int d_count;
    char **directories;
} dInd;

char *trimwhitespace(char *str);

int endFunc(int code, char *buffer);

int getPath(char **path);

int getLevel();

int directoryExist(char *path);

void logInFile(char *logFileName, char *message);

int readDirectory(char *src, int level, FILE *fp);

#endif //FILENAME_SCRAPPER_STRTOOLS_H
