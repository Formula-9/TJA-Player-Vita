#ifndef TJA_PLAYER_VITA_CHARTFILE_H
#define TJA_PLAYER_VITA_CHARTFILE_H

#include "Genre.h"
#include <stdio.h>

#define BUFFER_SIZE    4096
#define BYTES_TO_READ  BUFFER_SIZE-1

#define DATA_NOT_FOUND  0

#define TITLE_HEADER      "TITLE:"
#define SUBTITLE_HEADER   "SUBTITLE:"
#define DEMOSTART_HEADER  "DEMOSTART:"
#define MUSIC_FILE_HEADER "WAVE:"
#define LEVEL_HEADER      "LEVEL:"

#define EDIT_LEVEL_HEADER   "COURSE:Edit\r\n"
#define ONI_LEVEL_HEADER    "COURSE:Oni\r\n"
#define HARD_LEVEL_HEADER   "COURSE:Hard\r\n"
#define NORMAL_LEVEL_HEADER "COURSE:Normal\r\n"
#define EASY_LEVEL_HEADER   "COURSE:Easy\r\n"

typedef struct ChartFile {
    char *filePath;
    char *musicFile;
    char *title;
    char *subtitle;
    int diffEasy;
    int diffNormal;
    int diffHard;
    int diffOni;
    int diffEdit;
    float demoStart;
    Genre *genre;
} ChartFile;

ChartFile *makeChartFileInstance(char *filePath, Genre *genre);
void parseFileHeader(FILE *fileDescriptor, ChartFile *ChartFile);
void checkIfBufferEndsWithCourseAndReposition(FILE *fileDescriptor, char *buffer);
void repositionToClosestLineReturn(FILE *fileDescriptor, char *buffer);
void checkForMissingData(const char *buffer, ChartFile *chartFile);
int checkForIntTypeData(const char *buffer, const char *header);
float checkForFloatTypeData(const char *buffer, const char *header);
char *checkForStringTypeData(const char *buffer, const char *header);
void checkForLevelData(const char *buffer, ChartFile *file, const char *courseLevelHeader);
void checkForAnyLevelData(const char *buffer, ChartFile *file);
void freeChartFile(ChartFile *file);

#endif