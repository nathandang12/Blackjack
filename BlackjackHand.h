#ifndef BLACKJACKHAND_H
#define BLACKJACKHAND_H
#include "Hand.h"

//  the BlackjackHand class is derived from the Hand class and adds specific
//  member functions related to blackjack gameplay.
// It provides functions to check if the hand is a blackjack, if it has busted,
// or if it is a five-card charlie.
// These functions utilize the existing functionality inherited from the Hand
// class, such as getValue() and getCards(), to make determinations based on the
// value and number of cards in the hand.

// Class for a hand in Blackjack
class BlackjackHand : public Hand {
 public:
  bool isBlackjack() const;
  bool isBust() const;
  bool isFiveCardCharlie() const;
};

#endif