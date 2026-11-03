#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board() {
    rows = 4;
    cols = 4;
    initializeBoard();
}

void Board::initializeBoard() {
    int values[16] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};
    int index = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cards[i][j].value = values[index++];
            cards[i][j].isFlipped = false;
            cards[i][j].isMatched = false;
        }
    }
    shuffleCards();
}

void Board::shuffleCards() {
    srand((unsigned int)time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int randR = rand() % rows;
            int randC = rand() % cols;

            Card temp = cards[i][j];
            cards[i][j] = cards[randR][randC];
            cards[randR][randC] = temp;
        }
    }
}

bool Board::checkMatch(int r1, int c1, int r2, int c2) {
    if (cards[r1][c1].value == cards[r2][c2].value) {
        cards[r1][c1].isMatched = true;
        cards[r2][c2].isMatched = true;
        return true;
    }
    return false;
}

bool Board::isBoardComplete() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!cards[i][j].isMatched) {
                return false;
            }
        }
    }
    return true;
}