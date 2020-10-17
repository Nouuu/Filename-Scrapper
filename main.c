#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"

char *logFilename = "log.txt";
char *resultFile = "result.txt";

void logIt(char *message);

int main() {
    char *path = NULL;
    int returncode, level;

    if ((returncode = getPath(&path))) {
        logIt("Path empty");
        return endFunc(returncode, NULL);
    }


    if (!directoryExist(path)) {
        char *message = malloc(sizeof(char) * (strlen(path) + 20 + 1));
        sprintf(message, "Wrong directory : \"%s\"", path);

        logIt(message);
        free(message);
        return endFunc(1, path);
    }

    level = getLevel();

    FILE *fp = fopen(resultFile, "w");
    if (fp == NULL) {
        logIt("Cannot create result file !");
        return endFunc(1, path);
    }

    readDirectory(path, level, fp);

    fclose(fp);

    return endFunc(0, path);
}

void logIt(char *message) {
    logInFile(logFilename, message);
}



