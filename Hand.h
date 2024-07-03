#ifndef HAND_H
#define HAND_H

#include "BaseHand.h"
#include "Card.h"

// Hand class provides functionality to add cards, calculate the hand value, display the hand, and retrieve information about the hand's cards and size.
class Hand : public BaseHand {
public:
    Hand();
    ~Hand();
    void add(const Card &card);
    void clear();
    int getValue() const { return value; }
    void display() const;
    Card* getCards() const { return cards; }
    int getCardCount() const { return size; }
    friend ostream &operator<<(ostream &os, const Hand &hand);
    int getSize() const { return size; }

protected:
    Card* cards;
    int value;
    bool soft;
    int size;
    int capacity;
};

#endif