#include "TjaFile.h"

TjaFile *makeTjaFileInstance(char *filePath) {
    TjaFile *result = NULL;
    SceUID fileDescriptor;
    if ((fileDescriptor = sceIoOpen(filePath, SCE_O_RDONLY, 0777)) >= 0) {
        result = malloc(sizeof(TjaFile));
        if (result) {
            result->filePath = filePath;
            result->musicFile = NULL;
            result->diff_edit = result->diff_oni = result->diff_hard = result->diff_normal = result->diff_easy = DIFFICULTY_DATA_NOT_FOUND;
            writePointerToLogger(result);
            parseFileHeader(fileDescriptor, result);
        } else { writeToLogger("Error: couldn't allocate memory for TjaFile!"); }
        sceIoClose(fileDescriptor);
    } else {
        writeToLogger("Error: couldn't open file for reading!");
        free(filePath);
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
    static char buffer[512];
    while (sceIoRead(fileDescriptor, buffer, sizeof(buffer)) > 0) {
        checkIfBufferEndsWithCourseAndReposition(fileDescriptor, buffer);
        repositionToClosestLineReturn(fileDescriptor, buffer);
        if (!tjaFile->musicFile) checkForMusicFileName(buffer, tjaFile);
        checkForAnyLevelData(buffer, tjaFile);
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
        if (courseLevelHeader == EDIT_LEVEL_HEADER)  { file->diff_edit = strtol(position, NULL, 10); }
        else if (courseLevelHeader == ONI_LEVEL_HEADER) { file->diff_oni = strtol(position, NULL, 10); }
        else if (courseLevelHeader == HARD_LEVEL_HEADER) { file->diff_hard = strtol(position, NULL, 10); }
        else if (courseLevelHeader == NORMAL_LEVEL_HEADER) { file->diff_normal = strtol(position, NULL, 10); }
        else if (courseLevelHeader == EASY_LEVEL_HEADER) { file->diff_easy = strtol(position, NULL, 10); }
    }
}

/**
 * This function checks the buffer for any difficulty level that hasn't
 * been assigned yet in the TjaFile instance.
 * @param buffer
 * @param file
 */
void checkForAnyLevelData(const char *buffer, TjaFile *file) {
    if (file->diff_edit == DIFFICULTY_DATA_NOT_FOUND) { checkForLevelData(buffer, file, EDIT_LEVEL_HEADER); }
    if (file->diff_oni == DIFFICULTY_DATA_NOT_FOUND) { checkForLevelData(buffer, file, ONI_LEVEL_HEADER); }
    if (file->diff_hard == DIFFICULTY_DATA_NOT_FOUND) { checkForLevelData(buffer, file, HARD_LEVEL_HEADER); }
    if (file->diff_normal == DIFFICULTY_DATA_NOT_FOUND) { checkForLevelData(buffer, file, NORMAL_LEVEL_HEADER); }
    if (file->diff_easy == DIFFICULTY_DATA_NOT_FOUND) { checkForLevelData(buffer, file, EASY_LEVEL_HEADER); }
}

/**
 * This function searches the buffer for the music used by the chart.
 * @param buffer
 * @param file
 */
void checkForMusicFileName(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, MUSIC_FILE_HEADER);
    if (position != NULL) {
        position += strlen(MUSIC_FILE_HEADER);
        size_t musicFileNameSize = strcspn(position, "\r");
        char *musicFile = malloc(musicFileNameSize);
        if (musicFile) {
            strncpy(musicFile, position, musicFileNameSize);
            file->musicFile = musicFile;
        } else { writeToLogger("Error: couldn't allocate memory for music file name!");}
    }
}

void logTjaFile(TjaFile *tjaFile) {
    char buffer[512];
    snprintf(buffer, 512, "TjaFile: [filePath=%s; musicFile=%s; diff_easy=%d; diff_normal=%d; diff_hard=%d; diff_oni=%d; diff_edit=%d]",
             tjaFile->filePath, tjaFile->musicFile, tjaFile->diff_easy, tjaFile->diff_normal, tjaFile->diff_hard, tjaFile->diff_oni,
             tjaFile->diff_edit);
    writeToLogger(buffer);
}

/**
 * Free all memory used by the instance of TjaFile passed as parameter.
 * @param file The instance of TjaFile to free.
 */
void freeTjaFile(TjaFile *file) {
    /* Usually, these resources were allocated before the creation
     * of this instance. So they have to be freed. */
    free(file->filePath);
    free(file->musicFile);
    free(file);
}