#pragma once

class LevelManager {
public:
    int currentLevel;
    int unlockedLevel;

    LevelManager();
    int getMaxFlips();
    bool canPlayLevel(int level);
    void unlockNextLevel();
};