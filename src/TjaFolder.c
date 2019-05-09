#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/TjaFolder.h"
#include "../include/TjaFile.h"
#include "../include/Logger.h"

/**
 * Creates a new instance of TjaFolder.
 * @param folderName The name of the folder. Should be a music genre.
 * @param initialCapacity The initial capacity of the folder.
 * @return A pointer to the created instance, or NULL if the allocation failed.
 */
TjaFolder *newTjaFolder(char *folderName, int initialCapacity) {
    TjaFolder *folder = malloc(sizeof(char*) + sizeof(int) * 2 + sizeof(TjaFile*) * initialCapacity);
    if (folder) {
        memset(folder, 0, sizeof(TjaFolder));
        folder->folderName = folderName;
        folder->currentCapacity = initialCapacity;
    } else { writeToLogger("Couldn't allocate memory for TjaFolder!"); }
    return folder;
}

/**
 * Adds an instance of TjaFile to an existing TjaFolder. Note: if the folder have reached its maximum capacity,
 * it will call realloc. If this fails, an error will be logged, and the instance will be freed to avoid leaking
 * memory.
 * @param folder The TjaFolder instance to add a TjaFile instance to.
 * @param file The TjaFile instance to add to a TjaFolder.
 */
void addFileToFolder(TjaFolder *folder, TjaFile *file) {
    if (folder && file) {
        if (folder->numberOfFiles < folder->currentCapacity) {
            folder->files[folder->numberOfFiles] = file;
            folder->numberOfFiles++;
        } else {
            size_t newPtrSize = (sizeof(TjaFile*) * folder->currentCapacity) + (sizeof(TjaFile*) * TJAFOLDER_EXTRA_FILE_SLOTS);
            TjaFile **newFilesPtr = realloc(folder->files, newPtrSize);
            if (newFilesPtr) {
                folder->files = newFilesPtr;
                folder->files[folder->numberOfFiles] = file;
                folder->numberOfFiles++;
            } else {
                writeToLogger("Couldn't allocate extra memory for folder, the file won't be added.");
                freeTjaFile(file);
            }
        }
    }
}

/**
 * This functions calls the tjaFolderTitleQuickSort function and already provides the required data for it to work.
 * @param folder The instance of TjaFolder to sort.
 */
void sortTjaFolderByTitle(TjaFolder *folder) {
    tjaFolderTitleQuickSort(folder, 0, folder->numberOfFiles);
}

/**
 * Swap the addresses of two TjaFile pointers.
 * @param string1 The first TjaFile to swap.
 * @param string2 The second TjaFile to swap.
 */
void swapTjaFilePointers(TjaFile **file1, TjaFile **file2) {
    TjaFile *tmpPtr = *file1;
    *file1 = *file2;
    *file2 = tmpPtr;
}

/**
 * Sorts a section of a TjaFolder's "files" members, and return the index indicating where the
 * sorted section ends.
 * @param folder The TjaFolder to sort.
 * @param low Index indicating where to start sorting.
 * @param high Index indicating where to stop sorting.
 * @return An index indicating where the "files" member stops being sorted.
 */
int tjaFolderTitlePartition(TjaFolder *folder, int low, int high) {
    TjaFile *pivot = folder->files[low];
    int sortedIndex = low;
    for (int i = low + 1; i < high; i++) {
        if (strcmp(folder->files[i]->title, pivot->title) < 0) {
            swapTjaFilePointers(&folder->files[i], &folder->files[sortedIndex + 1]);
            sortedIndex++;
        }
    }
    swapTjaFilePointers(&pivot, &folder->files[sortedIndex]);
    return sortedIndex;
}

/**
 * Sorts a TjaFolder instance's "files" member based on the TJAs' titles.
 * @param folder The TjaFolder to sort.
 * @param low Index indicating where to start sorting.
 * @param high Index indicating where to stop sorting.
 */
void tjaFolderTitleQuickSort(TjaFolder *folder, int low, int high) {
    if (low < high) {
        int pivot = tjaFolderTitlePartition(folder, low, high);
        tjaFolderTitleQuickSort(folder, low, pivot);
        tjaFolderTitleQuickSort(folder, pivot+1, high);
    }
}

/**
 * Frees all the memory used by a TjaFolder and stored TjaFiles.
 * @param folder The instance of TjaFolder to free.
 */
void freeTjaFolder(TjaFolder *folder) {
    for (int i = 0; i < folder->numberOfFiles; i++) {
        freeTjaFile(folder->files[i]);
    }
    free(folder->folderName);
    free(folder);
}