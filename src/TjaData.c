#include <stdlib.h>
#include <stdio.h>
#include <psp2/io/fcntl.h>

#include "../include/TjaFile.h"
#include "../include/Logger.h"
#include "../include/Constants.h"
#include "../include/TjaData.h"

TjaData *makeTjaDataFromTjaFile(TjaFile *file, int level) {
    TjaData *result = NULL;
    SceUID fileDescriptor;
    if (file != NULL && (fileDescriptor = sceIoOpen(file->filePath, SCE_O_RDONLY, 0777)) >= 0) {
        result = calloc(1, sizeof(TjaData));
        if (result) {
            result->file = file;
            performFirstPass(result, level, fileDescriptor);
        }
        sceIoClose(fileDescriptor);
    } else { writeToLogger("Couldn't open the file for reading!"); }
    return result;
}

/**
 * Reads the course data for the specified Difficulty Level until the #END tag, and initializes the counters in
 * the data parameter.
 * @param data The course data that will be initialized.
 * @param level The desired course level.
 * @param fileDescriptor The file to perform the first pass on.
 */
void performFirstPass(TjaData *data, int level, SceUID fileDescriptor) {
    //TODO
    return;
}

/**
 * Logs the data contained in a TjaData instance to the log. Used for debugging purposes, and memory-heavy
 * data won't be logged (but their pointer will).
 * @param data A pointer to the instance of TjaData to log.
 */
void logTjaData(TjaData *data) {
    static char buffer[512];
    snprintf(buffer, 512, TJADATA_SPRINTF_FORMAT,
             data->file, data->notes, data->noteCount, data->balloonHits, data->balloonCount, data->bpmChange,
             data->bpmChangeCount, data->scrollChange, data->scrollChangeCount);
    writeToLogger(buffer);
}