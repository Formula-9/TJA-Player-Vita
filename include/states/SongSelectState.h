#ifndef TJA_PLAYER_VITA_SONGSELECTSTATE_H
#define TJA_PLAYER_VITA_SONGSELECTSTATE_H

void songSelectStateStart();
void songSelectStateUpdate();
void songSelectStateEnd();

// ================================================ //
// || Graphics-related functions                 || //
// ================================================ //
void initAllBg();
void freeAllBg();
void drawBg();

void initTriggerSprites();
void freeTriggerSprites();
void drawTriggerSprites();

// ================================================ //
// || Controls & Difficulty Change               || //
// ================================================ //
void handleButtons();
void raiseDifficulty();
void lowerDifficulty();

//*2: 0 = Random; 1 = Folder 0 / Song 0; Folder_0.SongNumber = Folder 1 / Song 0

#endif //TJA_PLAYER_VITA_SONGSELECTSTATE_H
