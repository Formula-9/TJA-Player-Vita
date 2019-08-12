#include "../include/ChartFinder.h"
#include "../include/ChartFile.h"
#include "../include/Genre.h"
#include "../include/Log.h"

#include <psp2/kernel/processmgr.h>

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

static Genre *currentGenre = NULL;
static bool isDone;

void runChartFinderThread() {
    int threadId = sceKernelCreateThread("chartfinder", vitaThreadWrap_searchForCharts, 0x10000100, 0x10000, 0, 0, NULL);
    if (threadId >= 0) {
        sceKernelStartThread(threadId, 0, 0);
    }
}

/**
 * This wraps the searchForCharts call in a way that makes it easy to call & block
 * execution in Title.
 */
int vitaThreadWrap_searchForCharts(SceSize args, void *argp) {
    isDone = false;
    searchForCharts(BASE_SEARCH_PATH, 0);
    isDone = true;
    return 0;
}

/**
 * Returns if the Vita Thread handling the chart search is done or not.
 */
bool isChartFinderVitaThreadDone() {
    return isDone;
}

/**
 * Look for charts in a folder.
 * @param path Where to start looking for files.
 * @param depth_level Indicate the current depth (folders entered without returning). Pass 
 */
void searchForCharts(const char *path, int depthLevel) {
    DIR *folderFileDescriptor = opendir(path);
    lookForGenreFile(path);
    struct dirent *dirEntry;
    while ((dirEntry = readdir(folderFileDescriptor)) != NULL) {
        if (strcmp(dirEntry->d_name, ".") == 0 || strcmp(dirEntry->d_name, "..") == 0) continue;
        char *pathToEntry = makePathFromDirAndString(path, dirEntry->d_name);
        if (isTjaFile(pathToEntry)) {
            ChartFile *chart = makeChartFileInstance(pathToEntry, currentGenre);
            appendChartNodeToTail(chart);
        } else if (isFolderAndNotParentOrCurrent(pathToEntry) && depthLevel < MAX_DEPTH_LEVEL) {
            searchForCharts(pathToEntry, depthLevel + 1);
        }   
        free(pathToEntry);
    }
    closedir(folderFileDescriptor);
}

/**
 * Opens the folder at specified path and look for a Genre.ini file.
 * If found, the file is then used to change the currentGenre Genre pointer,
 * and the new Genre pointer is appended to the genreLinkedList.
 */
void lookForGenreFile(const char *path) {
    DIR *folderFileDescriptor = opendir(path);
    struct dirent *dirEntry;
    int keepSearching = 1;
    while ((dirEntry = readdir(folderFileDescriptor)) != NULL && keepSearching) {
        if (strcmp(dirEntry->d_name, GENRE_FILE) == 0) {
            char *fileName = makePathFromDirAndString(path, dirEntry->d_name);
            currentGenre = createGenreStructFromFile(fileName);
            appendGenreNodeToTail(currentGenre);
            keepSearching = 0;
            free(fileName);
        }
    }
    closedir(folderFileDescriptor);
}

/**
 * Free the linked list containing all found charts.
 */
void destroyListOfFoundCharts() {
    freeChartLinkedList();
}

/**
 * Free the linked list containing all found genres.
 */
void destroyListOfFoundGenres() {
    freeGenreLinkedList();
}

/**
 * Determines if a directory entry is a TJA file or not.
 * @param dirEntry The directory entry to check.
 * @param pathToFile The path to the directory entry.
 * @return 1 if the entry is a TJA file, or 0 if it's a different kind of file.
 */
int isTjaFile(const char *pathToFile) {
    int result = 1;
    struct stat entryStat;
    stat(pathToFile, &entryStat);
    if (!S_ISREG(entryStat.st_mode) || (strncmp(getLastFourCharactersOfString(pathToFile), TJA_EXTENSION, 4) != 0)) result = 0;
    return result;
}

/**
 * Determines if a directory entry is a folder or not, and if it's a folder, not one that points to the current
 * folder (also known as ".") or to its parent (also known as "..") .
 * @param dirEntry The directory entry to check.
 * @param pathToFile The path to the directory entry.
 * @return 1 if the conditions are satisfied, or 0 if at least one of them aren't.
 */
int isFolderAndNotParentOrCurrent(const char *pathToFile) {
    return isFolder(pathToFile) && (strncmp(pathToFile, ".", 1) != 0) && (strncmp(pathToFile, "..", 2) != 0);
}

/**
 * Determines if a directory entry is a folder or not.
 * @param dirEntry he directory entry to check.
 * @param pathToFile The path to the directory entry.
 * @return 1 if the entry is a folder, or 0 if it isn't.
 */
int isFolder(const char *pathToFile) {
    struct stat entryStat;
    stat(pathToFile, &entryStat);
    return (S_ISDIR(entryStat.st_mode));
}

/**
 * This function determines the smallest size to allocate for a TITLE / SUBTITLE / WAVE string.
 * @param string The string that needs to be checked (ex: "TITLE: <SONGTITLE><line return>")
 * @return The size of the string to allocate.
 */
size_t getStringSize(char *string) {
    size_t stringSizeLineFeed = strcspn(string, "\n");
    size_t stringSizeCarriageReturn = strcspn(string, "\r");
    return stringSizeCarriageReturn < stringSizeLineFeed ? stringSizeCarriageReturn : stringSizeLineFeed;
}

/**
 * Return a pointer to the last 4 characters of a string. In this application, this is
 * mostly used to get a pointer to the file extension.
 * @param string The string to extract the last 4 characters from.
 * @return A pointer to the last 4 characters of the string.
 */
const char *getLastFourCharactersOfString(const char *string) {
    return (string + (strlen(string) - 4));
}

/**
 * Concatenates a base path and an extension (folder or a file to open), and return the string
 * resulting from that concatenation.
 * @param basePath The base path.
 * @param extensionPath The name of the folder/file to append to the base path.
 * @return A pointer to the created string. Remember to free it after usage!
 */
char *makePathFromDirAndString(const char *basePath, const char *extensionPath) {
    int basePathLength = strlen(basePath);
    int extensionPathLength = strlen(extensionPath);
    char *buffer = malloc(basePathLength + extensionPathLength + 2);
    if (buffer) {
        strcpy(buffer, basePath);
        buffer[basePathLength] = '/';
        strcpy(buffer + basePathLength + 1, extensionPath);
    }
    return buffer;
}

/**
 * Return all found charts in the form of a linked list.
 */
ChartNode *getListOfFoundCharts() {
    return getChartLinkedListHead();
}

GenreLinkedList *getListOfFoundGenres() {
    return getGenreLinkedListHead();
}