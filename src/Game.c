#include <stdlib.h>
#include <SDL/SDL.h>

// Core
#include "../include/Game.h"
#include "../include/ChartFinder.h"
#include "../include/Log.h"

// States
#include "../include/State.h"
#include "../include/Title.h"
#include "../include/SongSelect.h"

static vita2d_font *font = NULL;
static int nextState = STATE_ID_NO_STATE;

/**
 * Try to initialize all the subsystems needed by the application.
 * @return INIT_RESULT_OK if the application started correctly, INIT_RESULT_FAIL on failure.
 */
int startGame() {
    int startResult = INIT_RESULT_OK;
    int continueInit = 1;
    int initFuncsIter = 0;
    vita2d_init();
    openLogFile();
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
    int (*initFuncs[3])() = { initSDL, initSDLMixer, loadCommonResources };

    while (continueInit && initFuncsIter < 3) {
        continueInit = !(initFuncs[initFuncsIter]() == INIT_RESULT_FAIL);
        initFuncsIter++;
    }

    if (!continueInit) {
        quitGame();
        startResult = INIT_RESULT_FAIL;
    }

    return startResult;
}

/**
 * Initialize SDL.
 * @return INIT_RESULT_OK if the initialization was successful, INIT_RESULT_FAIL on error.
 */
int initSDL() {
    int initResult = INIT_RESULT_OK;
    if (SDL_Init(SDL_INIT_FLAGS) < 0) {
        printfToFile("SDL_Init: %s\n", SDL_GetError());
        initResult = INIT_RESULT_FAIL;
    }
    return initResult;
}

/**
 * Initialize SDL Mixer.
 * @return INIT_RESULT_OK if the initialization was successful, INIT_RESULT_FAIL on error.
 */
int initSDLMixer() {
    int initResult = INIT_RESULT_OK;
    if (Mix_Init(SDL_MIXER_FLAGS) != SDL_MIXER_FLAGS) {
        printfToFile("Mix_Init: %s\n", Mix_GetError());
        initResult = INIT_RESULT_FAIL;
    }
    return initResult;
}

/**
 * Load resources common to all of the game's states.
 * @return INIT_RESULT_OK if all resources were successfully loaded, INIT_RESULT_FAIL on error.
 */
int loadCommonResources() {
    int initResult = INIT_RESULT_OK;
    font = vita2d_load_font_file(GAME_FONT_FILE);
    if (!font) {
        initResult = INIT_RESULT_FAIL;
        printfToFile("Couldn't read font file at path: %s\n", GAME_FONT_FILE);
    }
    return initResult;
}

/**
 * Free all memory used by common resources.
 */
void destroyCommonResources() {
    vita2d_free_font(font);
    destroyListOfFoundCharts();
}

/**
 * Exit all SDL subsystems and vita2d.
 */
void quitGame() {
    destroyListOfFoundCharts();
    destroyListOfFoundGenres();
    Mix_Quit();
    SDL_Quit();
    closeLogFile();
    vita2d_fini();
}

/**
 * Register the state ID of the state to execute once the current one ends.
 * @param newState The ID of the state to execute after the current one.
 */
void registerNextState(int newState) {
    nextState = newState;
}

/**
 * Used to jump between states.
 */
void handleNextState() {
    void (*stateEntryFunc[])() = { prepareTitleData, prepareSongSelectData };
    int currentState;
    while (nextState != STATE_ID_NO_STATE) {
        currentState = nextState;
        nextState = STATE_ID_NO_STATE;
        (*stateEntryFunc[currentState])();
    }
}

/**
 * Return the font used by the application.
 */
vita2d_font *getFont() {
    return font;
}