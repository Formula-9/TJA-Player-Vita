#ifndef TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
#define TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H

void inGameRenderingStateStart();
void inGameRenderingStateUpdate();
void inGameRenderingStateEnd();

/* Init */
void initTopBg();
void initLaneLeftWindow();
void initNoteLane();
void initHitMark();

/* Draw */
void drawTopBg();
void drawLaneLeftWindow();
void drawNoteLane();
void drawHitMark();

#endif //TJA_PLAYER_VITA_INGAMERENDERINGSTATE_H
