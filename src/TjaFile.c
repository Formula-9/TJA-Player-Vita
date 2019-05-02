#include "TjaFile.h"

TjaFile *makeTjaFileInstance(char *filePath) {
    TjaFile *result = NULL;
    SceUID fileDescriptor;
    if ((fileDescriptor = sceIoOpen(filePath, SCE_O_RDONLY, 0777)) >= 0) {
        result = malloc(sizeof(TjaFile));
        if (result) {
            initBlankTjaFile(result);
            result->filePath = filePath;
            parseFileHeader(fileDescriptor, result);
        } else { writeToLogger("Error: couldn't allocate memory for TjaFile!"); }
        sceIoClose(fileDescriptor);
    } else {
        writeToLogger("Error: couldn't open file for reading!");
        free(filePath);
    }
    return result;
}

void initBlankTjaFile(TjaFile *file) {
    file->title = NULL;
    file->subtitle = NULL;
    file->musicFile = NULL;
    file->diffEdit = DATA_NOT_FOUND;
    file->diffOni = DATA_NOT_FOUND;
    file->diffHard = DATA_NOT_FOUND;
    file->diffNormal = DATA_NOT_FOUND;
    file->diffEasy = DATA_NOT_FOUND;
    file->bpm = DATA_NOT_FOUND;
    file->musicVolume = DATA_NOT_FOUND;
    file->soundEffectVolume = DATA_NOT_FOUND;
    file->scoreMode = DATA_NOT_FOUND;
    file->demoStart = 0.0f;
    file->offset = 0.0f;
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
    if (!tjaFile->title) { checkForTitleData(buffer, tjaFile); }
    if (!tjaFile->subtitle) { checkForSubtitleData(buffer, tjaFile); }
    if (!tjaFile->musicFile) { checkForMusicFileName(buffer, tjaFile); }
    if (!tjaFile->bpm) { checkForBpmData(buffer, tjaFile); }
    if (!tjaFile->musicVolume) { checkForMusicVolumeData(buffer, tjaFile); }
    if (!tjaFile->soundEffectVolume) { checkForSoundEffectVolumeData(buffer, tjaFile); }
    if (!tjaFile->scoreMode) { checkForScoreModeData(buffer, tjaFile); }
    if (!tjaFile->demoStart) { checkForDemoStartData(buffer, tjaFile); }
    if (!tjaFile->offset) { checkForOffsetData(buffer, tjaFile); }
    checkForAnyLevelData(buffer, tjaFile);
}

void checkForTitleData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, TITLE_HEADER);
    if (position != NULL) {
        position += strlen(TITLE_HEADER);
        size_t titleSize = strcspn(position, "\r");
        char *title = malloc(titleSize);
        if (title) {
            strncpy(title, position, titleSize);
            file->title = title;
        } else { writeToLogger("Error: couldn't allocate memory for title!");}
    }
}

void checkForSubtitleData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, SUBTITLE_HEADER);
    if (position != NULL) {
        position += strlen(SUBTITLE_HEADER);
        size_t subtitleSize = strcspn(position, "\r");
        char *subtitle = malloc(subtitleSize);
        if (subtitle) {
            strncpy(subtitle, position, subtitleSize);
            file->subtitle = subtitle;
        } else { writeToLogger("Error: couldn't allocate memory for subtitle!");}
    }
}
void checkForBpmData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, BPM_HEADER);
    if (position != NULL) {
        position += strlen(BPM_HEADER);
        file->bpm = strtol(position, NULL, 10);
    }
}

void checkForMusicVolumeData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, SONGVOL_HEADER);
    if (position != NULL) {
        position += strlen(SONGVOL_HEADER);
        file->musicVolume = strtol(position, NULL, 10);
    }
}

void checkForSoundEffectVolumeData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, SEVOL_HEADER);
    if (position != NULL) {
        position += strlen(SEVOL_HEADER);
        file->soundEffectVolume = strtol(position, NULL, 10);
    }
}

void checkForScoreModeData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, SCOREMODE_HEADER);
    if (position != NULL) {
        position += strlen(SCOREMODE_HEADER);
        file->scoreMode = strtol(position, NULL, 10);
    }
}

void checkForOffsetData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, OFFSET_HEADER);
    if (position != NULL) {
        position += strlen(OFFSET_HEADER);
        file->offset = strtof(position, NULL);
    }
}

void checkForDemoStartData(const char *buffer, TjaFile *file) {
    char *position = strstr(buffer, DEMOSTART_HEADER);
    if (position != NULL) {
        position += strlen(DEMOSTART_HEADER);
        file->demoStart = strtof(position, NULL);
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
        if (courseLevelHeader == EDIT_LEVEL_HEADER)  { file->diffEdit = strtol(position, NULL, 10); }
        else if (courseLevelHeader == ONI_LEVEL_HEADER) { file->diffOni = strtol(position, NULL, 10); }
        else if (courseLevelHeader == HARD_LEVEL_HEADER) { file->diffHard = strtol(position, NULL, 10); }
        else if (courseLevelHeader == NORMAL_LEVEL_HEADER) { file->diffNormal = strtol(position, NULL, 10); }
        else if (courseLevelHeader == EASY_LEVEL_HEADER) { file->diffEasy = strtol(position, NULL, 10); }
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

/**
 * This function searches the buffer for the music used by the chart.
 * @param buffer The buffer to check.
 * @param file The instance of TjaFile to update if data is found.
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
    snprintf(buffer, 512, TJAFILE_SPRINTF_FORMAT, tjaFile->filePath, tjaFile->title, tjaFile->subtitle, tjaFile->musicFile,
             tjaFile->diffEasy, tjaFile->diffNormal, tjaFile->diffHard, tjaFile->diffOni, tjaFile->diffEdit, tjaFile->bpm,
             tjaFile->musicVolume, tjaFile->soundEffectVolume, tjaFile->scoreMode, tjaFile->offset, tjaFile->demoStart);
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