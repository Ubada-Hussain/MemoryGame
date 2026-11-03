#include "LevelManager.h"

LevelManager::LevelManager() {
    currentLevel = 1;
    unlockedLevel = 1;
}

int LevelManager::getMaxFlips() {
    if (currentLevel == 1) return 30;      // Easy
    else if (currentLevel == 2) return 24; // Medium
    else if (currentLevel == 3) return 20; // Hard
    return 30;
}

bool LevelManager::canPlayLevel(int level) {
    return level <= unlockedLevel;
}

void LevelManager::unlockNextLevel() {
    if (currentLevel == unlockedLevel && unlockedLevel < 3) {
        unlockedLevel++;
    }
}