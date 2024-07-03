#include "Card.h"

Card::Card() : suit(HEARTS), rank(TWO) {}
Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

// getValue() function calculates and returns the numerical value of a card
// based on its rank It returns 10 for ranks TEN, JACK, QUEEN, and KING, 11 for
// an ACE, and the rank + 2 for ranks TWO to NINE
int Card::getValue() const {
  if (rank >= TEN) {
    return 10;
  } else if (rank == ACE) {
    return 11;
  } else {
    return rank + 2;
  }
}

Rank Card::getRank() const { return rank; }
Suit Card::getSuit() const { return suit; }


// the overloaded << operator enables Card objects to be printed to the output
// stream by combining the appropriate rank and suit names from predefined
// arrays e.g a Card object with the rank of TWO and the suit of HEARTS would be
// printed as "2H"
ostream &operator<<(ostream &os, const Card &card) {
  const char *suitNames[] = {"H", "D", "C", "S"};
  const char *rankNames[] = {"2", "3",  "4", "5", "6", "7", "8",
                             "9", "10", "J", "Q", "K", "A"};
  os << rankNames[card.getRank()] << suitNames[card.getSuit()];
  return os;
}