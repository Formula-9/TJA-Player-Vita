#ifndef _CHART_FINDER_H_
#define _CHART_FINDER_H_

#include "ChartLinkedList.h"
#include "GenreLinkedList.h"

#include <psp2/types.h>
#include <stdbool.h>

#define TJA_EXTENSION       ".tja"
#define MAX_DEPTH_LEVEL     3

#define GENRE_FILE          "genre.ini"
#define BASE_SEARCH_PATH    "ux0:/data/tjapvita/tja"   

void runChartFinderThread();
int vitaThreadWrap_searchForCharts(SceSize args, void *argp);
bool isChartFinderVitaThreadDone();
void searchForCharts(const char *path, int depthLevel);
void lookForGenreFile(const char *path);
void destroyListOfFoundCharts();
void destroyListOfFoundGenres();
int isTjaFile(const char *pathToFile);
int isFolderAndNotParentOrCurrent(const char *pathToFile);
int isFolder(const char *pathToFile);
size_t getStringSize(char *string);
const char *getLastFourCharactersOfString(const char *string);
char *makePathFromDirAndString(const char *basePath, const char *extensionPath);
ChartLinkedList *getListOfFoundCharts();
GenreLinkedList *getListOfFoundGenres();

#endif //_CHART_FINDER_H_