#pragma once
#include "raylib.h"
#include "Game.h"
#include <string>

enum ScreenState {
    SCREEN_NAME_ENTRY,
    SCREEN_MAIN_MENU,
    SCREEN_LEVEL_SELECT,
    SCREEN_GAMEPLAY,
    SCREEN_RESULT,
    SCREEN_LEADERBOARD,
    SCREEN_HOW_TO_PLAY
};

class GameGUI {
public:
    int screenWidth;
    int screenHeight;
    ScreenState currentState;
    std::string playerName;
    Game game;

    GameGUI();
    void run();
    
    void drawNameEntry();
    void drawMainMenu();
    void drawLevelSelect();
    void drawGameplay();
    void drawResult();
    void drawLeaderboard();
    void drawHowToPlay();
};