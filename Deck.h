#ifndef DECK_H
#define DECK_H

#include "Card.h"

// Deck class represents a deck of cards, provides public functions to shuffle
// deck, deal cards from the top, and check if deck is empty
class Deck {
public:
    Deck();
    ~Deck();
    void shuffle();
    Card deal();
    bool empty() const;

private:
    Card* cards;
    int size;
    int capacity;
};

#endif // DECK_H