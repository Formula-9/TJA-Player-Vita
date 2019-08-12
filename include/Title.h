#ifndef _TITLE_H_
#define _TITLE_H_

#define TITLE_OPTION_PLAY 0
#define TITLE_OPTION_EXIT 1

#define NOWLOADING_TEXT   "Searching for charts on the SD Card, please wait..."

#define TITLE_STATUS_CONTINUE           0
#define TITLE_STATUS_LAUNCH_SONGSELECT  1
#define TITLE_STATUS_QUIT               2

void prepareTitleData();
void drawTextWhileWaitingForChartFinderThread(char *str);
void updateTitle();
void titleHandleInput();
void incrementSelectedOption();
void decrementSelectedOption();
void changeTitleStatus();
void destroyTitleData();

#endif //_TITLE_H_