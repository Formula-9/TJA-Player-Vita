#include "../include/ChartFile.h"
#include "../include/SjisToUtf8.h"

#include <string.h>
#include <stdlib.h>

ChartFile *makeChartFileInstance(char *filePath, Genre *genre) {
    ChartFile *result = NULL;
    FILE *fileDescriptor = fopen(filePath, "r");
    if (fileDescriptor) {
        result = malloc(sizeof(ChartFile));
        if (result) {
            memset(result, 0, sizeof(ChartFile));
            result->genre = genre;
            result->filePath = strdup(filePath);
            parseFileHeader(fileDescriptor, result);
        }
        fclose(fileDescriptor);
    }
    return result;
}

/**
 * This function parses thea "header" parts of a TJA file, and
 * fills the required parts of the provided ChartFile instance.
 * @param fileDescriptor
 * @param ChartFile
 */
void parseFileHeader(FILE *fileDescriptor, ChartFile *ChartFile) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int readBytes = fread(buffer, sizeof(char), BYTES_TO_READ, fileDescriptor);
    while (readBytes > 0) {
        if (readBytes == BYTES_TO_READ) {
            checkIfBufferEndsWithCourseAndReposition(fileDescriptor, buffer);
            repositionToClosestLineReturn(fileDescriptor, buffer);
        }
        checkForMissingData(buffer, ChartFile);
        memset(buffer, 0, sizeof(buffer));
        readBytes = fread(buffer, sizeof(char), BYTES_TO_READ, fileDescriptor);
    }
}

/**
 * Checks if the buffer ends on a "COURSE:" header. If this is the case, exclude it from
 * the buffer, and rewind the cursor back by the size of the header.
 * @param fileDescriptor The file descriptor that will be moved back if necessary.
 * @param buffer The buffer to check and modify.
 */
void checkIfBufferEndsWithCourseAndReposition(FILE *fileDescriptor, char *buffer) {
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
        fseek(fileDescriptor, charactersToGoBack, SEEK_CUR);
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
void repositionToClosestLineReturn(FILE *fileDescriptor, char *buffer) {
    char *lastNewLineChar = strrchr(buffer, '\n');
    if (lastNewLineChar) {
        //lastNewLineChar;
        int charactersToGoBack = -strlen(lastNewLineChar);
        fseek(fileDescriptor, charactersToGoBack, SEEK_CUR);
        int nullTerminatorPosition = strlen(buffer) - strlen(lastNewLineChar);
        buffer[nullTerminatorPosition] = '\0';
    }
}

void checkForMissingData(const char *buffer, ChartFile *chartFile) {
    if (!chartFile->title) { chartFile->title = checkForStringTypeData(buffer, TITLE_HEADER); }
    if (!chartFile->subtitle) { chartFile->subtitle = checkForStringTypeData(buffer, SUBTITLE_HEADER); }
    if (!chartFile->musicFile) { chartFile->musicFile = checkForStringTypeData(buffer, MUSIC_FILE_HEADER); }
    if (!chartFile->demoStart) { chartFile->demoStart = checkForFloatTypeData(buffer, DEMOSTART_HEADER); }
    checkForAnyLevelData(buffer, chartFile);
}

int checkForIntTypeData(const char *buffer, const char *header) {
    char *position = strstr(buffer, header);
    int result = 0;
    if (position) {
        position += strlen(header);
        result = strtol(position, NULL, 10);
    }
    return result;
}

float checkForFloatTypeData(const char *buffer, const char *header) {
    char *position = strstr(buffer, header);
    float result = 0.0f;
    if (position) {
        position += strlen(header);
        result = strtof(position, NULL);
    }
    return result;
}

char *checkForStringTypeData(const char *buffer, const char *header) {
    char *position = strstr(buffer, header);
    char *result = NULL;
    if (position) {
        position += strlen(header);
        size_t stringSizeLineFeed = strcspn(position, "\n");
        size_t stringSizeCarriageReturn = strcspn(position, "\r");
        size_t stringSize = stringSizeCarriageReturn < stringSizeLineFeed ? stringSizeCarriageReturn : stringSizeLineFeed;
        char *string = malloc(stringSize + 1);
        if (string) {
            strncpy(string, position, stringSize);
            string[stringSize] = '\0';
            result = shiftJisToUtf8(string);
            free(string);
        }
    }
    return result;
}

/**
 * This functions checks if the buffer contains data about the
 * level for a given difficulty for a chart. If this is the case,
 * the diff_extreme member of the file parameter is set to the number found.
 * @param buffer The buffer to check.
 * @param file The ChartFile instance to write the difficulty level to.
 *
 */
void checkForLevelData(const char *buffer, ChartFile *file, const char *courseLevelHeader) {
    char *position = strstr(buffer, courseLevelHeader);
    if (position) {
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
 * been assigned yet in the ChartFile instance.
 * @param buffer The buffer to check.
 * @param file The instance of ChartFile to update if data is found.
 */
void checkForAnyLevelData(const char *buffer, ChartFile *file) {
    if (file->diffEdit == DATA_NOT_FOUND) { checkForLevelData(buffer, file, EDIT_LEVEL_HEADER); }
    if (file->diffOni == DATA_NOT_FOUND) { checkForLevelData(buffer, file, ONI_LEVEL_HEADER); }
    if (file->diffHard == DATA_NOT_FOUND) { checkForLevelData(buffer, file, HARD_LEVEL_HEADER); }
    if (file->diffNormal == DATA_NOT_FOUND) { checkForLevelData(buffer, file, NORMAL_LEVEL_HEADER); }
    if (file->diffEasy == DATA_NOT_FOUND) { checkForLevelData(buffer, file, EASY_LEVEL_HEADER); }
}

/**
 * Free all memory used by the instance of ChartFile passed as parameter.
 * @param file The instance of ChartFile to free.
 */
void freeChartFile(ChartFile *file) {
    if (file) {
        if (file->filePath) free(file->filePath);
        if (file->musicFile) free(file->musicFile);
        if (file->title) free(file->title);
        if (file->subtitle) free(file->subtitle);
        memset(file, 0, sizeof(ChartFile));
        free(file);
        file = NULL;
    }
}