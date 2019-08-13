#ifndef _TITLE_H_
#define _TITLE_H_

#define TITLE_OPTION_PLAY 0
#define TITLE_OPTION_EXIT 1

#define TITLE_WAIT_MESSAGE              "Now Loading"
#define TITLE_WAIT_MESSAGE_MAX_SIZE     "Now Loading..."
#define TITLE_WAIT_MESSAGE_FONT_SIZE    32

#define TITLE_PLAY_TEXT           "Play"
#define TITLE_EXIT_TEXT           "Exit"
#define TITLE_OPTION_FONT_SIZE    28

#define TITLE_STATUS_CONTINUE           0
#define TITLE_STATUS_LAUNCH_SONGSELECT  1
#define TITLE_STATUS_QUIT               2

#define TITLE_TEXTURE_ARROW_PATH        "ux0:/data/tjapvita/res/arrow.png"

#define TITLE_WAIT_DELAY                1000000
#define TITLE_UPD_DELAY                 33300

void prepareTitleData();
void updateNowLoadingText(char *str, int *numberOfPoints);
void drawTextWhileWaitingForChartFinderThread(char *str, int width, int height);
void updateTitle();
void drawTitleOptions();
void drawArrow(int textPosX, int textPosY);
void titleHandleInput();
void incrementSelectedOption();
void decrementSelectedOption();
void changeTitleStatus();
void destroyTitleData();

#endif //_TITLE_H_