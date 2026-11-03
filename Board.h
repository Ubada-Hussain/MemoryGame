#pragma once
#include "Card.h"

class Board {
public:
    Card cards[4][4];
    int rows;
    int cols;

    Board();
    void initializeBoard();
    void shuffleCards();
    bool checkMatch(int r1, int c1, int r2, int c2);
    bool isBoardComplete();
};