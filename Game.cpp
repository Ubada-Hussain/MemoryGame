#include "Game.h"

Game::Game() {
    matches = 0;
    flipsUsed = 0;
    gameOver = false;
    gameWon = false;
    selectedR1 = -1; selectedC1 = -1;
    selectedR2 = -1; selectedC2 = -1;
    flippedCount = 0;
    hideTimer = 0.0f;
    waitingToHide = false;
}

void Game::startLevel(int level) {
    levelManager.currentLevel = level;
    resetLevel();
}

void Game::resetLevel() {
    board.initializeBoard();
    matches = 0;
    flipsUsed = 0;
    gameOver = false;
    gameWon = false;
    selectedR1 = -1; selectedC1 = -1;
    selectedR2 = -1; selectedC2 = -1;
    flippedCount = 0;
    hideTimer = 0.0f;
    waitingToHide = false;
}

void Game::selectCard(int r, int c) {
    if (gameOver || waitingToHide) return;
    if (board.cards[r][c].isFlipped || board.cards[r][c].isMatched) return;

    board.cards[r][c].isFlipped = true;
    flipsUsed++;

    if (flippedCount == 0) {
        selectedR1 = r;
        selectedC1 = c;
        flippedCount = 1;
    } else if (flippedCount == 1) {
        selectedR2 = r;
        selectedC2 = c;
        flippedCount = 2;

        if (board.checkMatch(selectedR1, selectedC1, selectedR2, selectedC2)) {
            matches++;
            flippedCount = 0;
            selectedR1 = -1; selectedC1 = -1;
            selectedR2 = -1; selectedC2 = -1;

            if (board.isBoardComplete()) {
                gameOver = true;
                gameWon = true;
                levelManager.unlockNextLevel();
            }
        } else {
            waitingToHide = true;
            hideTimer = 0.8f;
        }
    }

    if (!gameWon && flipsUsed >= levelManager.getMaxFlips() && flippedCount == 0) {
        gameOver = true;
    }
}

void Game::update() {
    if (waitingToHide) {
        hideTimer -= 0.016f;
        if (hideTimer <= 0.0f) {
            board.cards[selectedR1][selectedC1].isFlipped = false;
            board.cards[selectedR2][selectedC2].isFlipped = false;
            flippedCount = 0;
            selectedR1 = -1; selectedC1 = -1;
            selectedR2 = -1; selectedC2 = -1;
            waitingToHide = false;

            if (flipsUsed >= levelManager.getMaxFlips() && !board.isBoardComplete()) {
                gameOver = true;
            }
        }
    }
}