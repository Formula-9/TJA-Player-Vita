#include "../include/Utils.h"

#include <string.h>
#include <stdlib.h>
#include <iconv.h>
#include <stdio.h>
#include <sys/stat.h>

#include "../include/Constants.h"
#include "../include/Logger.h"
#include "../include/TjaFile.h"

/**
 * Search the folder at folderPath and all its sub-folders recursively* for TJA files.
 * *Note: There is a depth limit. By default, the depth limit is 2, because the application
 * expects tht the TJA to be in DEFAULT_PATH/Genre/SongName/SongName.tja
 * @param folderPath The folder in which the application will look for TJA files.
 * @param depthLevel The current depth_level. For most cases, just provide zero.
 */
void findAllTjaFiles(const char *folderPath, int depthLevel) {
    DIR *folderFileDescriptor = opendir(folderPath);
    if (folderFileDescriptor) {
        struct dirent *dirEntry;
        while ((dirEntry = readdir(folderFileDescriptor)) != NULL) {
            if (isTjaFile(dirEntry, folderPath)) {
                char *pathToTja = makePathFromDirAndString(folderPath, dirEntry->d_name);
                TjaFile *tja = makeTjaFileInstance(pathToTja);
				free(pathToTja);
                logTjaFile(tja);
                freeTjaFile(tja);
            } else if (isFolderAndNotParentOrCurrent(dirEntry, folderPath) && depthLevel < MAX_DEPTH_LEVEL) {
                char *newPath = makePathFromDirAndString(folderPath, dirEntry->d_name);
                findAllTjaFiles(newPath, depthLevel + 1);
                free(newPath);
            }
        }
        closedir(folderFileDescriptor);
    } else { writeToLogger("Couldn't open directory for scan!"); }
}

/**
 * Determines if a directory entry is a TJA file or not.
 * @param dirEntry The directory entry to check.
 * @param folderPath The path to the directory entry.
 * @return 1 if the entry is a TJA file, or 0 if it's a different kind of file.
 */
int isTjaFile(struct dirent *dirEntry, const char *folderPath) {
    int result = 1;
    struct stat entryStat;
    char *pos = makePathFromDirAndString(folderPath, dirEntry->d_name);
    stat(pos, &entryStat);
    free(pos);
    if (!S_ISREG(entryStat.st_mode)) result = 0;
    if (result && (strncmp(getLastFourCharactersOfString(dirEntry->d_name), TJA_EXTENSION, 4) != 0)) result = 0;
    return result;
}

/**
 * Determines if a directory entry is a folder or not, and if it's a folder, not one that points to the current
 * folder (also known as ".") or to its parent (also known as "..") .
 * @param dirEntry The directory entry to check.
 * @param folderPath The path to the directory entry.
 * @return 1 if the conditions are satisfied, or 0 if at least one of them aren't.
 */
int isFolderAndNotParentOrCurrent(struct dirent *dirEntry, const char *folderPath) {
    return isFolder(dirEntry, folderPath) && (strncmp(dirEntry->d_name, ".", 1) != 0) && (strncmp(dirEntry->d_name, "..", 1) != 0);
}

/**
 * Determines if a directory entry is a folder or not.
 * @param dirEntry he directory entry to check.
 * @param folderPath The path to the directory entry.
 * @return 1 if the entry is a folder, or 0 if it isn't.
 */
int isFolder(struct dirent *dirEntry, const char *folderPath) {
    struct stat entryStat;
    char *pos = makePathFromDirAndString(folderPath, dirEntry->d_name);
    stat(pos, &entryStat);
    free(pos);
    return (S_ISDIR(entryStat.st_mode));
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
    } else { writeToLogger("Error: couldn't allocate memory to create a string!"); }
    return buffer;
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