#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <psp2/io/fcntl.h>

#include "../include/Utils.h"
#include "../include/TjaFile.h"
#include "../include/Constants.h"
#include "../include/Logger.h"
#include "../include/SjisToUtf8.h"

TjaFile *makeTjaFileInstance(char *filePath) {
    TjaFile *result = NULL;
    SceUID fileDescriptor;
    if ((fileDescriptor = sceIoOpen(filePath, SCE_O_RDONLY, 0777)) >= 0) {
        result = calloc(1, sizeof(TjaFile));
        if (result) {
            result->filePath = strdup(filePath);
            parseFileHeader(fileDescriptor, result);
        } else { writeToLogger("Error: couldn't allocate memory for TjaFile!"); }
        sceIoClose(fileDescriptor);
    } else {
        writeToLogger("Error: couldn't open file for reading!");
    }
    return result;
}

/**
 * This function parses thea "header" parts of a TJA file, and
 * fills the required parts of the provided TjaFile instance.
 * @param fileDescriptor
 * @param tjaFile
 */
void parseFileHeader(SceUID fileDescriptor, TjaFile *tjaFile) {
    static char buffer[BUFFER_SIZE];
    while (sceIoRead(fileDescriptor, buffer, sizeof(buffer)) > 0) {
        checkIfBufferEndsWithCourseAndReposition(fileDescriptor, buffer);
        repositionToClosestLineReturn(fileDescriptor, buffer);
        checkForMissingData(buffer, tjaFile);
    }
}

/**
 * Checks if the buffer ends on a "COURSE:" header. If this is the case, exclude it from
 * the buffer, and rewind the cursor back by the size of the header.
 * @param fileDescriptor The file descriptor that will be moved back if necessary.
 * @param buffer The buffer to check and modify.
 */
void checkIfBufferEndsWithCourseAndReposition(SceUID fileDescriptor, char *buffer) {
    char *headers[5] = {EDIT_LEVEL_HEADER, ONI_LEVEL_HEADER, HARD_LEVEL_HEADER, NORMAL_LEVEL_HEADER, EASY_LEVEL_HEADER};
    int repositionned = 0;
    int iterator = 0;
    char *position = NULL;
    while (iterator < 5 && !repositionned) {
        position = strstr(buffer, headers[iterator]);
        if (position != NULL && position[strlen(headers[iterator])] == '\0') { repositionned = 1; }
        else { iterator++; }
    }

    if (repositionned) {
        int charactersToGoBack = -strlen(headers[iterator]);
        sceIoLseek(fileDescriptor, charactersToGoBack, SCE_SEEK_CUR);
        int nullTerminatorPosition = strlen(buffer) - strlen(position);
        buffer[nullTerminatorPosition] = '\0';
    }
}

/**
 * This function cuts the buffer at the last line return found,
 * and sets the cursor back from the number of characters removed from the buffer.
 * @param fileDescriptor The file descriptor that will be set back.
 * @param buffer The buffer that will be truncated.
 */
void repositionToClosestLineReturn(SceUID fileDescriptor, char *buffer) {
    char *lastNewLineChar = strrchr(buffer, '\n') + 1;
    int charactersToGoBack = -strlen(lastNewLineChar);
    sceIoLseek(fileDescriptor, charactersToGoBack, SCE_SEEK_CUR);
    int nullTerminatorPosition = strlen(buffer) - strlen(lastNewLineChar);
    buffer[nullTerminatorPosition] = '\0';
}

void checkForMissingData(const char *buffer, TjaFile *tjaFile) {
    if (!tjaFile->title) { checkForStringTypeData(buffer, &tjaFile->title, TITLE_HEADER); }
    if (!tjaFile->subtitle) { checkForStringTypeData(buffer, &tjaFile->subtitle, SUBTITLE_HEADER); }
    if (!tjaFile->musicFile) { checkForStringTypeData(buffer, &tjaFile->musicFile, MUSIC_FILE_HEADER); }
    if (!tjaFile->bpm) { checkForFloatTypeData(buffer, &tjaFile->bpm, BPM_HEADER); }
    if (!tjaFile->musicVolume) { checkForIntTypeData(buffer, &tjaFile->musicVolume, SONGVOL_HEADER); }
    if (!tjaFile->soundEffectVolume) { checkForIntTypeData(buffer, &tjaFile->soundEffectVolume, SEVOL_HEADER); }
    if (!tjaFile->scoreMode) { checkForIntTypeData(buffer, &tjaFile->scoreMode, SCOREMODE_HEADER); }
    if (!tjaFile->demoStart) { checkForFloatTypeData(buffer, &tjaFile->demoStart, DEMOSTART_HEADER); }
    if (!tjaFile->offset) { checkForFloatTypeData(buffer, &tjaFile->offset, OFFSET_HEADER); }
    checkForAnyLevelData(buffer, tjaFile);
}

void checkForIntTypeData(const char *buffer, int *result, const char *header) {
    char *position = strstr(buffer, header);
    if (position != NULL) {
        position += strlen(header);
        *result = strtol(position, NULL, 10);
    }
}

void checkForFloatTypeData(const char *buffer, float *result, const char *header) {
    char *position = strstr(buffer, header);
    if (position != NULL) {
        position += strlen(header);
        *result = strtof(position, NULL);
    }
}

void checkForStringTypeData(const char *buffer, char **result, const char *header) {
    char *position = strstr(buffer, header);
    if (position != NULL) {
        position += strlen(header);
        size_t stringSizeLineFeed = strcspn(position, "\n");
        size_t stringSizeCarriageReturn = strcspn(position, "\r");
        size_t stringSize = stringSizeCarriageReturn < stringSizeLineFeed ? stringSizeCarriageReturn : stringSizeLineFeed;
        char *string = malloc(stringSize + 1);
        if (string) {
            strncpy(string, position, stringSize);
            string[stringSize] = '\0';
            *result = shiftJisToUtf8(string);
            free(string);
        } else { writeToLogger("Error: couldn't allocate memory for music file name!");}
    }
}

/**
 * This functions checks if the buffer contains data about the
 * level for a given difficulty for a chart. If this is the case,
 * the diff_extreme member of the file parameter is set to the number found.
 * @param buffer The buffer to check.
 * @param file The TJAFile instance to write the difficulty level to.
 *
 */
void checkForLevelData(const char *buffer, TjaFile *file, const char *courseLevelHeader) {
    char *position = strstr(buffer, courseLevelHeader);
    if (position != NULL) {
        position += strlen(courseLevelHeader) + strlen(LEVEL_HEADER);
        if (!strcmp(courseLevelHeader, EDIT_LEVEL_HEADER)) { file->diffEdit = strtol(position, NULL, 10); }
        else if (!strcmp(courseLevelHeader, ONI_LEVEL_HEADER)) { file->diffOni = strtol(position, NULL, 10); }
        else if (!strcmp(courseLevelHeader, HARD_LEVEL_HEADER)) { file->diffHard = strtol(position, NULL, 10); }
        else if (!strcmp(courseLevelHeader, NORMAL_LEVEL_HEADER)) { file->diffNormal = strtol(position, NULL, 10); }
        else if (!strcmp(courseLevelHeader, EASY_LEVEL_HEADER)) { file->diffEasy = strtol(position, NULL, 10); }
    }
}

/**
 * This function checks the buffer for any difficulty level that hasn't
 * been assigned yet in the TjaFile instance.
 * @param buffer The buffer to check.
 * @param file The instance of TjaFile to update if data is found.
 */
void checkForAnyLevelData(const char *buffer, TjaFile *file) {
    if (file->diffEdit == DATA_NOT_FOUND) { checkForLevelData(buffer, file, EDIT_LEVEL_HEADER); }
    if (file->diffOni == DATA_NOT_FOUND) { checkForLevelData(buffer, file, ONI_LEVEL_HEADER); }
    if (file->diffHard == DATA_NOT_FOUND) { checkForLevelData(buffer, file, HARD_LEVEL_HEADER); }
    if (file->diffNormal == DATA_NOT_FOUND) { checkForLevelData(buffer, file, NORMAL_LEVEL_HEADER); }
    if (file->diffEasy == DATA_NOT_FOUND) { checkForLevelData(buffer, file, EASY_LEVEL_HEADER); }
}

void logTjaFile(TjaFile *tjaFile) {
    static char buffer[512];
    snprintf(buffer, 512, TJAFILE_SPRINTF_FORMAT, tjaFile->filePath, tjaFile->title, tjaFile->subtitle,
             tjaFile->musicFile,
             tjaFile->diffEasy, tjaFile->diffNormal, tjaFile->diffHard, tjaFile->diffOni, tjaFile->diffEdit,
             tjaFile->bpm,
             tjaFile->musicVolume, tjaFile->soundEffectVolume, tjaFile->scoreMode, tjaFile->subtitleEffect,
             tjaFile->offset,
             tjaFile->demoStart);
    writeToLogger(buffer);
}

/**
 * Free all memory used by the instance of TjaFile passed as parameter.
 * @param file The instance of TjaFile to free.
 */
void freeTjaFile(TjaFile *file) {
    free(file->filePath);
    free(file->musicFile);
    free(file->title);
    free(file->subtitle);
    free(file);
}