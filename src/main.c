#include "../include/Game.h"
#include "../include/Title.h"

int main() {
    if (startGame() == INIT_RESULT_OK) {
        prepareTitleData();
    };
    quitGame();
    return 0;
}