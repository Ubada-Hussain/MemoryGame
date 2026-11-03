#pragma once

struct Card {
    int value;
    bool isFlipped;
    bool isMatched;

    Card() {
        value = 0;
        isFlipped = false;
        isMatched = false;
    }
};