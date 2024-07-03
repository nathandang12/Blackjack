#ifndef BLACKJACKGAME_H
#define BLACKJACKGAME_H

#include "BlackjackHand.h"
#include "Deck.h"

// the BlackjackGame class represents a game of Blackjack and provides member
// functions to handle various aspects of the game, including dealing cards,
// player and dealer turns, determining the winner, updating game statistics,
// and managing the game's currency or money system. The class encapsulates the
// game logic and provides an interface to play the game and interact with the
// game state.
class BlackjackGame {
 public:
  BlackjackGame();
  void play();

 private:
  Deck deck;
  BlackjackHand playerHand;
  BlackjackHand dealerHand;
  int playerWins;
  int dealerWins;
  int ties;
  int playerCurrency; // Player's currency
  bool doubledDown;
  void dealInitialCards();
  char getHitOrStandDecision();
  char getPlayAgainDecision();
  void playerTurn(int gambleAmount);
  void dealerTurn();
  void endRound();
  void printResult() const;
  void updateRecord() const;
  void updateGameOutcome(int gameAmount);
  void printCurrency() const;  // Print player's currency
  void printMenu() const;
};

#endif