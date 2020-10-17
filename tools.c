//
// Created by Unknow on 17/10/2020.
//

#include "tools.h"

char *trimwhitespace(char *str) {
    char *end;
    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

int endFunc(int code, char *buffer) {
    if (buffer != NULL) {
        free(buffer);
    }
    return code;
}

int getPath(char **path) {
    char *buff = malloc(sizeof(char) * 255 * 255 + 1);
    char *tmp;

    printf("Enter directory path :\n");
    fflush(stdin);
    fflush(stdout);
    if (fgets(buff, 255 * 255, stdin) == NULL) {
        return endFunc(1, buff);
    }
    if (buff[0] == '\n') {
        return endFunc(1, buff);
    }

    buff = strtok(buff, "\n");

    tmp = trimwhitespace(buff);

    if (strlen(tmp) == 0) {
        return endFunc(1, buff);
    }

    *path = malloc(sizeof(char) * (strlen(tmp) + 1));
    strcpy(*path, tmp);
    free(buff);

    printf("Path: |%s|\n", *path);
    return 0;
}

int getLevel() {
    int level;
    printf("Enter deep level to scan :\n");
    fflush(stdin);
    scanf("%d", &level);
    if (level <= 0) {
        return 1;
    }
    return level;
}

int directoryExist(char *path) {
    DIR *d = opendir(path);
    if (d != NULL) {
        closedir(d);
        return 1;
    }
    return 0;
}

int readDirectory(char *src, int level, FILE *fp) {
    if (level <= 0) {
        return 0;
    }
    char *newPath = malloc(sizeof(char) * (strlen(src) + 256 + 2));
    DIR *d = opendir(src);
    struct dirent *dir;

    dInd dInd1;
    dInd1.d_count = 0;
    dInd1.directories = malloc(sizeof(char *) * 1000);


    if (d) {
        fprintf(fp, "----Reading :%s----\n", src);
        while ((dir = readdir(d)) != NULL) {
            if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
                continue;

            struct stat buff;
            sprintf(newPath, "%s/%s", src, dir->d_name);
            if (stat(newPath, &buff) < 0) {
                fprintf(stderr, "error\n");
            } else if (S_ISDIR(buff.st_mode)) {
                dInd1.directories[dInd1.d_count] = malloc(sizeof(char) * (strlen(newPath) + 1));
                strcpy(dInd1.directories[dInd1.d_count], newPath);
                dInd1.d_count += 1;
            } else {
                fprintf(fp, "%s\n", dir->d_name);
            }
        }
        fprintf(fp, "\n");
        closedir(d);
    }

    if (dInd1.d_count) {
        for (int i = 0; i < dInd1.d_count; ++i) {
            readDirectory(dInd1.directories[i], level - 1, fp);
            free(dInd1.directories[i]);
        }
    }
    free(dInd1.directories);
    free(newPath);
    return 0;
}

void logInFile(char *logFileName, char *message) {
    char buff[20];
    struct tm *sTm;
    FILE *fp = fopen(logFileName, "a+");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open log file !");
        return;
    }
    if (!strlen(message)) {
        fprintf(stderr, "Message empty");
        return;
    }

    time_t now = time(0);
    sTm = gmtime(&now);
    strftime(buff, sizeof(buff), "%d-%m-%Y %H:%M:%S", sTm);

    printf("[%s] %s\n", buff, message);
    fprintf(fp, "[%s] %s\n", buff, message);
    fclose(fp);
}
