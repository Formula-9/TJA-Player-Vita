#include "../include/Utils.h"

/**
 * Search the folder at folderPath and all its sub-folders recursively* for TJA files.
 * *Note: There is a depth limit. By default, the depth limit is 2, because the application
 * expects tht the TJA to be in DEFAULT_PATH/Genre/SongName/SongName.tja
 * @param folderPath The folder in which the application will look for TJA files.
 * @param depthLevel The current depth_level. For most cases, just provide zero.
 */
void findAllTjaFiles(const char *folderPath, int depthLevel) {
    SceUID folderFileDescriptor = sceIoDopen(folderPath);
    if (folderFileDescriptor >= 0) {
        SceIoDirent dirEntry;
        while (sceIoDread(folderFileDescriptor, &dirEntry) > 0) {
            if (isTjaFile(dirEntry)) {
                char *pathToTja = makePathFromDirAndString(folderPath, dirEntry.d_name);
                TjaFile *tja = makeTjaFileInstance(pathToTja);
                freeTjaFile(tja);
            } else if (isFolderAndNotParentOrCurrent(dirEntry) && depthLevel < MAX_DEPTH_LEVEL) {
                char *newPath = makePathFromDirAndString(folderPath, dirEntry.d_name);
                findAllTjaFiles(newPath, depthLevel + 1);
                free(newPath);
            }
        }
        sceIoDclose(folderFileDescriptor);
    }
}

/**
 * Determines if a directory entry is a TJA file or not.
 * @param dirEntry The directory entry to check.
 * @return 1 if the entry is a TJA file, or 0 if it's a different kind of file.
 */
int isTjaFile(SceIoDirent dirEntry) {
    int result = 1;
    if (!SCE_S_ISREG(dirEntry.d_stat.st_mode)) result = 0;
    if (result && (strncmp(getLastFourCharactersOfString(dirEntry.d_name), TJA_EXTENSION, 4) != 0)) result = 0;
    return result;
}

/**
 * Determines if a directory entry is a folder or not, and if it's a folder, not one that points to the current
 * folder (also known as ".") or to its parent (also known as "..") .
 * @param dirEntry The directory entry to check.
 * @return 1 if the conditions are satisfied, or 0 if at least one of them aren't.
 */
int isFolderAndNotParentOrCurrent(SceIoDirent dirEntry) {
    return isFolder(dirEntry) && (strncmp(dirEntry.d_name, ".", 1) != 0) && (strncmp(dirEntry.d_name, "..", 1) != 0);
}

/**
 * Determines if a directory entry is a folder or not.
 * @param dirEntry he directory entry to check.
 * @return 1 if the entry is a folder, or 0 if it isn't.
 */
int isFolder(SceIoDirent dirEntry) {
    return (SCE_S_ISDIR(dirEntry.d_stat.st_mode));
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