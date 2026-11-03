#pragma once
#include "Board.h"
#include "LevelManager.h"

class Game {
public:
    Board board;
    LevelManager levelManager;
    
    int matches;
    int flipsUsed;
    bool gameOver;
    bool gameWon;

    int selectedR1, selectedC1;
    int selectedR2, selectedC2;
    int flippedCount;
    float hideTimer;
    bool waitingToHide;

    Game();
    void startLevel(int level);
    void resetLevel();
    void selectCard(int r, int c);
    void update();
};