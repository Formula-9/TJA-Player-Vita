#include <psp2/kernel/processmgr.h>
#include <vita2d.h>
#include <string.h>
#include <psp2/ctrl.h>

#include "../include/Title.h"
#include "../include/Game.h"
#include "../include/ChartLinkedList.h"
#include "../include/ChartFinder.h"
#include "../include/State.h"
#include "../include/Log.h"

static int status = TITLE_STATUS_CONTINUE;
static int selectedOption = TITLE_OPTION_PLAY;
static vita2d_texture *arrow = NULL;

void prepareTitleData() {
    arrow = vita2d_load_PNG_file(TITLE_TEXTURE_ARROW_PATH);
    if (!arrow) {
        printfToFile("Ressource missing: %s\n", TITLE_TEXTURE_ARROW_PATH);
    } else {
        runChartFinderThread();
        int width, height, numberOfPoints = 0;
        char str[15];
        vita2d_font_text_dimensions(getFont(), GAME_FONT_SIZE, TITLE_WAIT_MESSAGE_MAX_SIZE, &width, &height);
        while (!isChartFinderVitaThreadDone()) {
            updateNowLoadingText(str, &numberOfPoints);
            drawTextWhileWaitingForChartFinderThread(str, width, height);
            sceKernelDelayThread(TITLE_WAIT_DELAY);
        }
        updateTitle();
    }
}

/**
 * Update the "Now Loading" message by adding points after it (like most game do in their
 * loading screens).
 * @param str The string to update.
 * @param numberOfPoints A pointer to the int variable containing the number of points.
 */
void updateNowLoadingText(char *str, int *numberOfPoints) {
    strcpy(str, TITLE_WAIT_MESSAGE);
    for (int i = 0; i < *numberOfPoints; i++) strcat(str, ".");

    if (*numberOfPoints < 3) {
        (*numberOfPoints)++;
    } else {
        *numberOfPoints = 0;
    }
}

/**
 * Only used while waiting for the ChartFinder thread to finish, draws the "Now Loading"
 * message on screen after clearing it.
 */
void drawTextWhileWaitingForChartFinderThread(char *str, int width, int height) {
    vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_font_draw_text(getFont(), (VITA_SCREEN_W / 2) - (width / 2), (VITA_SCREEN_H / 2) - (height / 2), RGBA8(255, 255, 255, 255), TITLE_WAIT_MESSAGE_FONT_SIZE, str);
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
        vita2d_start_drawing();
        vita2d_clear_screen();
        
        drawTitleOptions();
        
        vita2d_end_drawing();
        vita2d_swap_buffers();
        sceKernelDelayThread(TITLE_UPD_DELAY);
    }

    destroyTitleData();
    switch(status) {    //TODO: Call appropriate functions.
        case TITLE_STATUS_LAUNCH_SONGSELECT:
            registerNextState(STATE_ID_SONGSELECT);
            break;
        case TITLE_STATUS_QUIT:
            break;
        default:
            break;
    }
}

/**
 * Draws the options on the screen, and also draw the arrow next
 * to the selected option.
 */
void drawTitleOptions() {
    char *options[] = {TITLE_PLAY_TEXT, TITLE_EXIT_TEXT};
    int iterator = 0;
    int optionsLength = sizeof(options)/sizeof(char*);
    int width, height;
    while (iterator < optionsLength) {
        vita2d_font_text_dimensions(getFont(), TITLE_OPTION_FONT_SIZE, options[iterator], &width, &height);
        int positionX = (VITA_SCREEN_W / 2) - (width / 2);
        int positionY = (VITA_SCREEN_H / 1.5) + (2 * height * iterator);
        vita2d_font_draw_text(getFont(), positionX, positionY, RGBA8(255, 255, 255, 255), TITLE_OPTION_FONT_SIZE, options[iterator]);
        if (iterator == selectedOption) {
            drawArrow(positionX, positionY);
        }
        iterator++;
    }
}

/**
 * Draws an arrow next to the currently selected option.
 */
void drawArrow(int textPosX, int textPosY) {
    unsigned int width = vita2d_texture_get_width(arrow);
    unsigned int height = vita2d_texture_get_height(arrow);
    int positionX = textPosX - (1.5 * width);
    int positionY = textPosY - (0.8 * height);
    vita2d_draw_texture(arrow, positionX, positionY);
}

/**
 * Handles button presses.
 */
void titleHandleInput() {
    SceCtrlData ctrl;
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

/**
 * Called when Circle is pressed, used to confirm the selection and quit the
 * main update loop for the Title Screen.
 */
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

/**
 * Should be used to clean up anything that was alloc'd on the heap. 
 */
void destroyTitleData() {
    vita2d_free_texture(arrow);
}