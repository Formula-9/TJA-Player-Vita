#include "../include/Title.h"
#include "../include/Game.h"
#include "../include/ChartLinkedList.h"
#include "../include/ChartFinder.h"

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <vita2d.h>

static int status = TITLE_STATUS_CONTINUE;
static int selectedOption = TITLE_OPTION_PLAY;
static SceCtrlData ctrl;

void prepareTitleData() {
    runChartFinderThread();
    int width, height, numberOfPoints = 0;
    char str[15] = "Now Loading";
    vita2d_font_text_dimensions(getFont(), GAME_FONT_SIZE, str, &width, &height);
    while (!isChartFinderVitaThreadDone()) {
        updateNowLoadingText(str, &numberOfPoints);
        drawTextWhileWaitingForChartFinderThread(str, width, height);
        sceKernelDelayThread(DEFAULT_DELAY);
    }
}

/**
 * Update the "Now Loading" message by adding points after it (like most game do in their
 * loading screens).
 * @param str The string to update.
 * @param numberOfPoints A pointer to the int variable containing the number of points.
 */
void updateNowLoadingText(char *str, int *numberOfPoints) {
    for (int i = 0; i < *numberOfPoints; i++) str[12 + i] = '.';
    str[12 + *numberOfPoints] = '\0';

    if (*numberOfPoints < 3) {
        *numberOfPoints++;
    } else {
        *numberOfPoints = 0;
    }
}

/**
 * Only used while waiting for the ChartFinder thread to finish, draws the "Now Loading"
 * message on screen after clearing it.
 */
void drawTextWhileWaitingForChartFinderThread(char *str, int width, int height) {
    vita2d_clear_screen();
    vita2d_start_drawing();
    vita2d_font_draw_text(getFont(), (VITA_SCREEN_W / 2) - (width / 2), (VITA_SCREEN_H / 2) - (height / 2), RGBA8(255, 255, 255, 255), GAME_FONT_SIZE, str);
    vita2d_end_drawing();
    vita2d_swap_buffers();
}

/**
 * Update the Title Screen by drawing to the screen, and handling input.
 * This method is called once the chart loading thread has finished.
 */
void updateTitle() {
    while (status == TITLE_STATUS_CONTINUE) {
        titleHandleInput();
        vita2d_clear_screen();
        vita2d_start_drawing();

        vita2d_end_drawing();
        vita2d_swap_buffers();
        sceKernelDelayThread(DEFAULT_DELAY);
    }

    destroyTitleData();
    switch(status) {    //TODO: Call appropriate functions.
        case TITLE_STATUS_LAUNCH_SONGSELECT:
            break;
        case TITLE_STATUS_QUIT:
            break;
        default:
            break;
    }
}

void titleHandleInput() {
    sceCtrlPeekBufferPositive(0, &ctrl, 1);
    if (ctrl.buttons == SCE_CTRL_DOWN) {
        incrementSelectedOption();
    } else if (ctrl.buttons == SCE_CTRL_UP) {
        decrementSelectedOption();
    } else if (ctrl.buttons == SCE_CTRL_CIRCLE) {
        changeTitleStatus();
    }
}

/**
 * Called when pressing down. Move the "selected option" up by one.
 */
void incrementSelectedOption() {
    if (selectedOption < TITLE_OPTION_EXIT) {
        selectedOption++;
    } else {
        selectedOption = TITLE_OPTION_PLAY;
    }
}

/**
 * Called when pressing down. Move the "selected option" down by one.
 */
void decrementSelectedOption() {
    if (selectedOption > TITLE_OPTION_PLAY) {
        selectedOption--;
    } else {
        selectedOption = TITLE_OPTION_EXIT;
    }
}

void changeTitleStatus() {
    switch (selectedOption) {
        case (TITLE_OPTION_PLAY):
            status = TITLE_STATUS_LAUNCH_SONGSELECT;
            break;
        case (TITLE_OPTION_EXIT):
            status = TITLE_STATUS_QUIT;
            break;
    }
}

void destroyTitleData() {

}