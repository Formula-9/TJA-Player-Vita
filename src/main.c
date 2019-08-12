#include "../include/Game.h"
#include "../include/State.h"

int main() {
    if (startGame() == INIT_RESULT_OK) {
        registerNextState(STATE_ID_TITLE);
        handleNextState();
    };
    quitGame();
    return 0;
}