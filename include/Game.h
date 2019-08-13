#ifndef _GAME_H_
#define _GAME_H_

#include <vita2d.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <psp2/ctrl.h>

#define VITA_SCREEN_W       960
#define VITA_SCREEN_H       544

#define SDL_INIT_FLAGS      SDL_INIT_AUDIO
#define SDL_MIXER_FLAGS     MIX_INIT_OGG

#define INIT_RESULT_OK      0
#define INIT_RESULT_FAIL    1

#define GAME_FONT_FILE      "ux0:/data/tjapvita/res/font.ttf"
#define GAME_FONT_SIZE      24

#define DEFAULT_DELAY       16600

int startGame();
int initSDL();
int initSDLMixer();
int loadCommonResources();
void destroyCommonResources();
void quitGame();
void registerNextState(int newState);
void handleNextState();
vita2d_font *getFont();

#endif //_GAME_H_