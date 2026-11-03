#include "GameGUI.h"
#include <iostream>

GameGUI::GameGUI() {
    screenWidth = 800;
    screenHeight = 600;
    currentState = SCREEN_NAME_ENTRY;
    playerName = "";
}

void GameGUI::run() {
    InitWindow(screenWidth, screenHeight, "Memory Card Matching Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            case SCREEN_NAME_ENTRY:
                drawNameEntry();
                break;
            case SCREEN_MAIN_MENU:
                drawMainMenu();
                break;
            case SCREEN_LEVEL_SELECT:
                drawLevelSelect();
                break;
            case SCREEN_GAMEPLAY:
                drawGameplay();
                break;
            case SCREEN_RESULT:
                drawResult();
                break;
            case SCREEN_LEADERBOARD:
                drawLeaderboard();
                break;
            case SCREEN_HOW_TO_PLAY:
                drawHowToPlay();
                break;
        }

        EndDrawing();
    }

    CloseWindow();
}

void GameGUI::drawNameEntry() {
    DrawText("ENTER YOUR NAME", 280, 150, 24, DARKBLUE);

    Rectangle textBox = { 250, 220, 300, 40 };
    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);

    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (playerName.length() < 15)) {
            playerName += (char)key;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !playerName.empty()) {
        playerName.pop_back();
    }

    DrawText(playerName.c_str(), (int)textBox.x + 10, (int)textBox.y + 10, 20, BLACK);

    Rectangle btnContinue = { 320, 300, 160, 40 };
    DrawRectangleRec(btnContinue, DARKBLUE);
    DrawText("CONTINUE", 345, 310, 20, WHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, btnContinue) && !playerName.empty()) {
            currentState = SCREEN_MAIN_MENU;
        }
    }
}

void GameGUI::drawMainMenu() {
    DrawText("MEMORY CARD MATCHING GAME", 180, 80, 26, DARKBLUE);
    std::string welcomeStr = "Welcome, " + playerName + "!";
    DrawText(welcomeStr.c_str(), 300, 130, 20, DARKGRAY);

    Rectangle btnStart = { 300, 180, 200, 45 };
    Rectangle btnLeaderboard = { 300, 245, 200, 45 };
    Rectangle btnHowToPlay = { 300, 310, 200, 45 };
    Rectangle btnChangeName = { 300, 375, 200, 45 };
    Rectangle btnExit = { 300, 440, 200, 45 };

    DrawRectangleRec(btnStart, BLUE);
    DrawText("START GAME", 335, 192, 20, WHITE);

    DrawRectangleRec(btnLeaderboard, BLUE);
    DrawText("LEADERBOARD", 330, 257, 20, WHITE);

    DrawRectangleRec(btnHowToPlay, BLUE);
    DrawText("HOW TO PLAY", 335, 322, 20, WHITE);

    DrawRectangleRec(btnChangeName, BLUE);
    DrawText("CHANGE NAME", 330, 387, 20, WHITE);

    DrawRectangleRec(btnExit, DARKGRAY);
    DrawText("EXIT", 375, 452, 20, WHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, btnStart)) {
            currentState = SCREEN_LEVEL_SELECT;
        } else if (CheckCollisionPointRec(mouse, btnLeaderboard)) {
            currentState = SCREEN_LEADERBOARD;
        } else if (CheckCollisionPointRec(mouse, btnHowToPlay)) {
            currentState = SCREEN_HOW_TO_PLAY;
        } else if (CheckCollisionPointRec(mouse, btnChangeName)) {
            currentState = SCREEN_NAME_ENTRY;
        } else if (CheckCollisionPointRec(mouse, btnExit)) {
            CloseWindow();
        }
    }
}

void GameGUI::drawLevelSelect() {
    DrawText("SELECT DIFFICULTY", 270, 80, 26, DARKBLUE);

    Rectangle btnEasy = { 300, 180, 200, 50 };
    Rectangle btnMedium = { 300, 260, 200, 50 };
    Rectangle btnHard = { 300, 340, 200, 50 };
    Rectangle btnBack = { 300, 440, 200, 40 };

    DrawRectangleRec(btnEasy, GREEN);
    DrawText("EASY (30 Flips)", 325, 195, 18, WHITE);

    if (game.levelManager.canPlayLevel(2)) {
        DrawRectangleRec(btnMedium, ORANGE);
        DrawText("MEDIUM (24 Flips)", 315, 275, 18, WHITE);
    } else {
        DrawRectangleRec(btnMedium, LIGHTGRAY);
        DrawText("MEDIUM (LOCKED)", 315, 275, 18, DARKGRAY);
    }

    if (game.levelManager.canPlayLevel(3)) {
        DrawRectangleRec(btnHard, RED);
        DrawText("HARD (20 Flips)", 325, 355, 18, WHITE);
    } else {
        DrawRectangleRec(btnHard, LIGHTGRAY);
        DrawText("HARD (LOCKED)", 325, 355, 18, DARKGRAY);
    }

    DrawRectangleRec(btnBack, DARKGRAY);
    DrawText("BACK TO MENU", 330, 450, 18, WHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, btnEasy)) {
            game.startLevel(1);
            currentState = SCREEN_GAMEPLAY;
        } else if (CheckCollisionPointRec(mouse, btnMedium) && game.levelManager.canPlayLevel(2)) {
            game.startLevel(2);
            currentState = SCREEN_GAMEPLAY;
        } else if (CheckCollisionPointRec(mouse, btnHard) && game.levelManager.canPlayLevel(3)) {
            game.startLevel(3);
            currentState = SCREEN_GAMEPLAY;
        } else if (CheckCollisionPointRec(mouse, btnBack)) {
            currentState = SCREEN_MAIN_MENU;
        }
    }
}

void GameGUI::drawGameplay() {
    std::string levelStr = "Level: " + std::to_string(game.levelManager.currentLevel);
    std::string matchStr = "Matches: " + std::to_string(game.matches) + " / 8";
    std::string flipsStr = "Flips Left: " + std::to_string(game.levelManager.getMaxFlips() - game.flipsUsed);

    DrawText(levelStr.c_str(), 50, 20, 20, DARKBLUE);
    DrawText(matchStr.c_str(), 250, 20, 20, DARKBLUE);
    DrawText(flipsStr.c_str(), 500, 20, 20, RED);

    Rectangle btnRestart = { 650, 10, 120, 30 };
    DrawRectangleRec(btnRestart, ORANGE);
    DrawText("RESTART", 665, 17, 16, WHITE);

    int startX = 200;
    int startY = 80;
    int cardSize = 100;
    int gap = 15;

    Vector2 mouse = GetMousePosition();

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            Rectangle cardRect = { (float)(startX + c * (cardSize + gap)), (float)(startY + r * (cardSize + gap)), (float)cardSize, (float)cardSize };

            if (game.board.cards[r][c].isMatched) {
                DrawRectangleRec(cardRect, GREEN);
                DrawText(std::to_string(game.board.cards[r][c].value).c_str(), (int)cardRect.x + 40, (int)cardRect.y + 30, 40, WHITE);
            } else if (game.board.cards[r][c].isFlipped) {
                DrawRectangleRec(cardRect, RAYWHITE);
                DrawRectangleLines((int)cardRect.x, (int)cardRect.y, (int)cardRect.width, (int)cardRect.height, BLUE);
                DrawText(std::to_string(game.board.cards[r][c].value).c_str(), (int)cardRect.x + 40, (int)cardRect.y + 30, 40, BLUE);
            } else {
                DrawRectangleRec(cardRect, BLUE);
                DrawRectangleLines((int)cardRect.x, (int)cardRect.y, (int)cardRect.width, (int)cardRect.height, DARKBLUE);
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, cardRect)) {
                game.selectCard(r, c);
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, btnRestart)) {
        game.resetLevel();
    }

    if (game.gameOver) {
        currentState = SCREEN_RESULT;
    }
}

void GameGUI::drawResult() {
    if (game.gameWon) {
        DrawText("LEVEL COMPLETE!", 270, 150, 30, GREEN);
    } else {
        DrawText("LEVEL FAILED!", 300, 150, 30, RED);
    }

    std::string matchStr = "Matches Found: " + std::to_string(game.matches) + " / 8";
    std::string flipsStr = "Flips Used: " + std::to_string(game.flipsUsed);

    DrawText(matchStr.c_str(), 310, 220, 20, DARKGRAY);
    DrawText(flipsStr.c_str(), 330, 260, 20, DARKGRAY);

    Rectangle btnRetry = { 220, 340, 160, 45 };
    Rectangle btnMenu = { 420, 340, 160, 45 };
    Rectangle btnNext = { 320, 410, 160, 45 };

    DrawRectangleRec(btnRetry, ORANGE);
    DrawText("RETRY", 270, 352, 20, WHITE);

    DrawRectangleRec(btnMenu, BLUE);
    DrawText("MAIN MENU", 445, 352, 20, WHITE);

    if (game.gameWon && game.levelManager.currentLevel < 3) {
        DrawRectangleRec(btnNext, GREEN);
        DrawText("NEXT LEVEL", 340, 422, 20, WHITE);
    }

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, btnRetry)) {
            game.resetLevel();
            currentState = SCREEN_GAMEPLAY;
        } else if (CheckCollisionPointRec(mouse, btnMenu)) {
            currentState = SCREEN_MAIN_MENU;
        } else if (game.gameWon && game.levelManager.currentLevel < 3 && CheckCollisionPointRec(mouse, btnNext)) {
            game.startLevel(game.levelManager.currentLevel + 1);
            currentState = SCREEN_GAMEPLAY;
        }
    }
}

void GameGUI::drawLeaderboard() {
    DrawText("LEADERBOARD", 310, 100, 28, DARKBLUE);
    DrawText("No saved records yet.", 290, 220, 20, GRAY);
    DrawText("(File handling will be added in Phase 3)", 200, 260, 18, LIGHTGRAY);

    Rectangle btnBack = { 320, 400, 160, 40 };
    DrawRectangleRec(btnBack, DARKGRAY);
    DrawText("BACK", 375, 410, 20, WHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, btnBack)) {
        currentState = SCREEN_MAIN_MENU;
    }
}

void GameGUI::drawHowToPlay() {
    DrawText("HOW TO PLAY", 320, 80, 28, DARKBLUE);

    DrawText("1. Click two face-down cards to reveal them.", 180, 160, 18, BLACK);
    DrawText("2. If the numbers match, they remain revealed.", 180, 200, 18, BLACK);
    DrawText("3. If they don't match, they flip back down.", 180, 240, 18, BLACK);
    DrawText("4. Find all 8 matching pairs before flips run out.", 180, 280, 18, BLACK);
    DrawText("5. Complete Easy to unlock Medium, and Medium for Hard.", 180, 320, 18, BLACK);

    Rectangle btnBack = { 320, 420, 160, 40 };
    DrawRectangleRec(btnBack, DARKGRAY);
    DrawText("BACK", 375, 430, 20, WHITE);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse, btnBack)) {
        currentState = SCREEN_MAIN_MENU;
    }
}