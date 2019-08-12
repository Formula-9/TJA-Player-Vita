#include "../include/SongSelect.h"
#include "../include/Game.h"
#include "../include/ChartLinkedList.h"
#include "../include/ChartFinder.h"

#include <psp2/kernel/processmgr.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vita2d.h>

static ChartLinkedList *head = NULL;
static ChartLinkedList *tail = NULL;
static ChartLinkedList *currentChart = NULL;
static Mix_Music *demo = NULL;


void prepareSongSelectData() {
    head = getChartLinkedListHead();
    tail = getChartLinkedListTail();
    currentChart = head;
}

void updateSongSelect() {
    vita2d_clear_screen();
    vita2d_start_drawing();

    //When playing music...
    //Mix_SetMusicPosition(currentChart->data->demoStart);
    //if (Mix_PlayMusic(demo, -1))

    //if Down/Up pressed
    //

    vita2d_end_drawing();
    vita2d_swap_buffers();
    sceKernelDelayThread(DEFAULT_DELAY);
}

void destroySongSelectData() {

}