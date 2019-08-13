#include "../include/SongSelect.h"
#include "../include/Game.h"
#include "../include/ChartLinkedList.h"
#include "../include/ChartFinder.h"
#include "../include/State.h"

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vita2d.h>
#include <stdbool.h>

static ChartLinkedList *head = NULL;
static ChartLinkedList *tail = NULL;
static ChartLinkedList *previousPreviousChart = NULL;
static ChartLinkedList *previousChart = NULL;
static ChartLinkedList *currentChart = NULL;
static ChartLinkedList *nextChart = NULL;
static ChartLinkedList *nextNextChart = NULL;
static Mix_Music *demo = NULL;
static int status = SONGSELECT_STATUS_CONTINUE;

// Objective: Taiko Switch-like interface
//     [[< L] Current Genre  [R >]]
// [Score E]  [ Music - 2 ]
// [Score N]  [ Music - 1 ]
// [Score H]> [ Current M ]
// [Score O]  [ E/N/H/O/E ]
// [Score E]  [ Music + 1 ]
//            [ Music + 2 ]
// [ ===== Button Explaination ===== ]

void prepareSongSelectData() {
    head = getChartLinkedListHead();
    tail = getChartLinkedListTail();

    previousChart = tail;
    previousPreviousChart = getPreviousChartNode(previousChart);
    if (!previousPreviousChart) previousPreviousChart = previousChart;
    currentChart = head;
    nextChart = head->next;
    if (!nextChart) nextChart = head;
    nextNextChart = nextChart->next;
    if (!nextNextChart) nextNextChart = nextChart;
}

void updateSongSelect() {
    while (status == SONGSELECT_STATUS_CONTINUE) {
        songSelectHandleInput();
        vita2d_start_drawing();
        vita2d_clear_screen();

        drawMusicBoxes();
        //When playing music...
        //Mix_SetMusicPosition(currentChart->data->demoStart);
        //if (Mix_PlayMusic(demo, -1))

        vita2d_end_drawing();
        vita2d_swap_buffers();
        sceKernelDelayThread(DEFAULT_DELAY);
    }

    destroySongSelectData();
    switch(status) {
        case (SONGSELECT_STATUS_EXIT_TO_TITLE):
            registerNextState(STATE_ID_TITLE);
            break;
        default:
            break;
    }
}

//TODO: Not tested yet...
void drawMusicBoxes() {
    ChartNode *nodes[] = {previousPreviousChart, previousChart, currentChart, nextChart, nextNextChart};
    int iterator = 0;
    int length = (sizeof(nodes) / sizeof(ChartNode*));
    int positionX = (VITA_SCREEN_W /2) - (MUSIC_BOX_WIDTH / 2);
    bool drawingAfterCurrentChart = false;
    while (iterator < length) {
        int positionY = 64 + iterator * MUSIC_BOX_HEIGHT;
        RGBColor color = nodes[iterator]->data->genre->genreColor;
        if (nodes[iterator] == currentChart) {
            positionY = (VITA_SCREEN_H /2) - (MUSIC_CURRENT_SONG_BOX_HEIGHT / 2);
            drawingAfterCurrentChart = true;
            vita2d_draw_rectangle(positionX, positionY, MUSIC_BOX_WIDTH, MUSIC_CURRENT_SONG_BOX_HEIGHT, RGBA8(color.r, color.g, color.b, 255));
        } else {
            if (drawingAfterCurrentChart) {
                positionY = VITA_SCREEN_H - (MUSIC_BOX_HEIGHT * iterator);
            }
            vita2d_draw_rectangle(positionX, positionY, MUSIC_BOX_WIDTH, MUSIC_BOX_HEIGHT, RGBA8(color.r, color.g, color.b, 255));
        }
        iterator++;
    }
}

//TODO
void drawMusicTitles() {

}

void songSelectHandleInput() {
    SceCtrlData ctrl;
    sceCtrlPeekBufferPositive(0, &ctrl, 1);
    if (ctrl.buttons == SCE_CTRL_DOWN) {
        moveToNextSong();
    } else if (ctrl.buttons == SCE_CTRL_UP) {
        moveToPreviousSong();
    } else if (ctrl.buttons == SCE_CTRL_CROSS) {
        status = SONGSELECT_STATUS_EXIT_TO_TITLE;
    }
}

/**
 * Move pointers to the next song.
 */
void moveToNextSong() {
    previousPreviousChart = previousChart;
    previousChart = currentChart;
    currentChart = nextChart;
    nextChart = nextNextChart;
    if (nextNextChart == tail) {
        nextNextChart = head;
    } else {
        nextNextChart = nextNextChart->next;
    }
}

/**
 * Move pointers to the previous song.
 */
void moveToPreviousSong() {
    nextNextChart = nextChart;
    nextChart = currentChart;
    currentChart = previousChart;
    previousChart = previousPreviousChart;
    if (previousPreviousChart == head) {
        previousPreviousChart = tail;
    } else {
        previousPreviousChart = getPreviousChartNode(previousPreviousChart);
    }
}

void destroySongSelectData() {

}