#ifndef CARD_H
#define CARD_H

#include <iostream>
using namespace std;


// Using "enum" to define a set of named values starting with the Suit of a card.
enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

// Defining the value of each card
enum Rank {
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  ACE
};

// 'Card' class to represent individual cards in a deck, it has private members
// suit and rank and includes public methods to access these members
class Card {
 public:

  Card();
  Card(Suit s, Rank r);

  // Getters and other member functions
  int getValue() const;
  Rank getRank() const;
  Suit getSuit() const;

  // Overloaded operator
  friend ostream &operator<<(ostream &os, const Card &card); // "friend" declaration allows the function to access the private members of the 'Card' class

 private:
  Suit suit;
  Rank rank;
};

#endif