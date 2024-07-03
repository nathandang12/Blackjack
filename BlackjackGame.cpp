#include "BlackjackGame.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Constants
const string RECORD_FILE = "record.txt";

// the BlackjackGame::BlackjackGame() constructor initializes a BlackjackGame
// object by setting the initial values of the data members. It initializes the
// win counts (playerWins, dealerWins, and ties) to 0 and the player's currency
// (playerCurrency) to 1000. Additionally, it sets the seed for the random
// number generator based on the current time to ensure randomness in the game.

BlackjackGame::BlackjackGame()
    : playerWins(0), dealerWins(0), ties(0), playerCurrency(1000) {
  srand(time(nullptr));
}

// the dealInitialCards() function in the BlackjackGame class deals the initial
// two cards to both the player and the dealer. It adds cards to the respective
// playerHand and dealerHand objects by calling the add() function and obtaining
// the cards from the deck object using the deal() function. This function sets
// up the initial state of the game by providing the initial cards to start
// playing the Blackjack game.
void BlackjackGame::dealInitialCards() {
  playerHand.add(deck.deal());
  dealerHand.add(deck.deal());
  playerHand.add(deck.deal());
  dealerHand.add(deck.deal());
}

// playerTurn() function in the BlackjackGame class represents the player's turn
// in a game of Blackjack.

void BlackjackGame::playerTurn(int gambleAmount) {
  char choice;
  bool canDoubleDown =
      (playerHand.getSize() == 2);  // Check if player has two cards
  do {
    string input;
    cout << "\nYour hand: " << playerHand << endl;
    if (playerHand.isBlackjack() || playerHand.isFiveCardCharlie()) {
      break; // displays the player's hand and checks if the player has a blackjack or
       // a five-card charlie, terminating the turn if true.
    }

    while (true) {
      cout << "Do you want to hit (H), stand (S), or double down (D)? ";
      cin >> input;

      if (input.length() == 1 &&
          (input[0] == 'H' || input[0] == 'S' || input[0] == 'D')) {
        choice = input[0];
        break;
      } // Inside a loop, the player is prompted to input their decision and
         // the input is validated.

      cout << "Invalid input! Please enter 'H' (hit), 'S' (stand), or 'D' "
              "(double down).\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (choice == 'H') {
      playerHand.add(deck.deal());
      if (playerHand.isBust()) {
        cout << "Your hand: " << playerHand << endl;
        cout << "You busted!\n";
      } // If the player chooses to hit, a card is added to their hand and a
         // message is displayed if they bust (hand value exceeds 21).
    } else if (choice == 'D') {
      if (canDoubleDown) {
        if (playerCurrency < gambleAmount * 2) {
          cout << "You don't have enough money to double down. Please choose "
                  "another option.\n"; // If the player chooses to double down it checks if they are eligible andhave enough money. 
                                        // If so, the gamble amount is doubled, a card is added to their hand, and the loop is terminated.
        } else {
          playerCurrency -= gambleAmount;  // Deduct double of gamble amount for double down
          gambleAmount *= 2;
          playerHand.add(deck.deal());
          cout << "Your hand: " << playerHand << endl;
          doubledDown = true;
          break;
        }
      } else {
        cout << "You cannot double down at this point.\n";
      }
    } else if (choice != 'S') {
      cout << "Invalid input! Please enter 'H' (hit), 'S' (stand), or 'D' "
              "(double down).\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while (!playerHand.isBust() && choice != 'S');
} // The loop continues until the player busts or chooses to stand.


// dealerTurn() function in the BlackjackGame class represents the dealer's turn in a game of Blackjack. 
// It continues to draw cards until the value of the dealer's hand is 17 or higher. 
// After the dealer's turn, the dealer's hand is displayed, and if the dealer busts (exceeds 21), a corresponding message is printed. 
void BlackjackGame::dealerTurn() {
  while (dealerHand.getValue() < 17) {
    dealerHand.add(deck.deal());
  }
  cout << "Dealer's hand: " << dealerHand << endl;
  if (dealerHand.isBust()) {
    cout << "Dealer busted!\n";
  }
}

// the endRound() function in the BlackjackGame class clears the dealer and player's hand when called
void BlackjackGame::endRound() {
  playerHand.clear();
  dealerHand.clear();
}

// the printResult() function in the BlackjackGame class prints the Player's Win count, Dealer's Win count and the amount of ties that have occured since playing when called.
void BlackjackGame::printResult() const {
  cout << "\nPlayer wins: " << playerWins << "\nDealer wins: " << dealerWins
       << "\nTies: " << ties << "\n";
}

// the updateRecord() function in the BlackjackGame class is responsible for updating and storing the game record to a file. 
// It opens an output file stream, writes the values of playerWins, dealerWins, and ties to the file, and then closes the file. 
// This function allows for the preservation and tracking of game statistics across different sessions or runs of the Blackjack game.
void BlackjackGame::updateRecord() const {
  ofstream fout(RECORD_FILE);
  fout << playerWins << ' ' << dealerWins << ' ' << ties;
  fout.close();
}

// the updateGameOutcome() function in the BlackjackGame class determines the outcome of the game based on the final hands of the player and the dealer. 
// It updates the win counters (playerWins and dealerWins), the tie counter (ties), and the player's currency (playerCurrency) based on the outcome. 
// The function considers scenarios where the player wins, the dealer wins, or there is a tie. It also handles the doubling of the player's currency when they win.
void BlackjackGame::updateGameOutcome(int gambleAmount) {
  if (playerHand.isBust()) {
    dealerWins++;

  } else if (dealerHand.isBust() ||
             playerHand.getValue() > dealerHand.getValue() ||
             playerHand.isBlackjack()) {
    playerWins++;
    playerCurrency += doubledDown ? 4 * gambleAmount : 2 * gambleAmount;  // Add 2x gamble amount when player wins
  } else if (playerHand.getValue() < dealerHand.getValue()) {
    dealerWins++;

  } else {
    ties++;
    playerCurrency += gambleAmount;  // enter a push where neither player or
                                     // dealer win, money is returned to player
  }
    // Reset doubledDown at the end of each round
  doubledDown = false;
}

// the getHitOrStandDecision() function in the BlackjackGame class prompts the player to enter a decision of whether to hit or stand. 
// It validates the input, allowing only 'H' or 'S' (case-insensitive). 
// The function ensures that the player enters a valid decision and returns the decision character. 
// It handles input errors and provides error messages to guide the player.
char BlackjackGame::getHitOrStandDecision() {
  char decision;

  while (true) {
    cout << "Do you want to hit or stand? (H/S): ";
    cin >> decision;
    decision = toupper(decision);

    if (decision == 'H' || decision == 'S') {
      break;
    }

    cout << "Invalid input! Please enter 'H' or 'S'.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  return decision;
}

// the getPlayAgainDecision() function in the BlackjackGame class prompts the player to enter a decision of whether they want to play again or not. 
// It validates the input, allowing only 'Y' or 'N' (case-insensitive). 
// The function ensures that the player enters a valid decision and returns the decision character. It handles input errors and provides error messages to guide the player.
char BlackjackGame::getPlayAgainDecision() {
  char decision;

  while (true) {
    cout << "\nWould you like to play again? (Y/N): ";
    cin >> decision;
    decision = toupper(decision);

    if (decision == 'Y' || decision == 'N') {
      break;
    }

    cout << "Invalid input! Please enter 'Y' or 'N'.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  return decision;
}

// the printCurrency() function in the BlackjackGame class prints the player's current amount of currency when called
void BlackjackGame::printCurrency() const {
  cout << "Currency: $" << playerCurrency << endl;
}

// the printMenu() function in the BlackjackGame class displays the main menu when the game is initially run
void BlackjackGame::printMenu() const {
  cout << "=== Blackjack Game ===" << endl;
  cout << "1. Play Blackjack" << endl;
  cout << "2. Game Rules" << endl;
  cout << "3. Quit" << endl;
}

void BlackjackGame::play() {

// starts by prompting the player to choose an option from the game menu by calling the printMenu function and reading the player's choice using cin.
  int choice;
  bool validChoice = false;
  do {
    printMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        validChoice = true; // The validChoice flag is set to true to exit the menu loop.
        cout << "\nLet's play Blackjack!" << endl;
        deck.shuffle(); // The deck is shuffled using deck.shuffle().
        dealInitialCards(); // Initial cards are dealt to the player and the dealer by calling dealInitialCards().

    // The player is prompted to enter the amount of money they want to gamble.
        int gambleAmount;
        while (true) {
          string input;
          cout << "Your current balance: $" << playerCurrency << endl;
          cout << "Enter the amount of money you want to gamble: ";
          cin >> input;
          stringstream ss(input);
          if (ss >> gambleAmount && !(ss >> input)) {
            if (gambleAmount <= playerCurrency && gambleAmount > 0) {  // Input validation is performed to ensure a positive numeric value within the player's available currency.
              playerCurrency -= gambleAmount; // The player's currency is updated accordingly, and the gambling amount is stored in gambleAmount.
              break;
            } else {
              cout << "Invalid amount! Your bet must be positive and cannot "
                      "exceed your current balance."
                   << endl;

                   
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
          } else {
            cout << "Invalid input! Please enter a numeric value." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
          }
        }
        // If the player doesn't have enough money to gamble, the game ends.
        if (playerCurrency < 0) {
          cout << "You don't have enough money to gamble. Game over!" << endl;
          return; 
        }

        // The player takes their turn by calling playerTurn(gambleAmount).
        playerTurn(gambleAmount);
        if (!playerHand.isBust()) {
          dealerTurn(); // If the player hasn't busted, the dealer takes their turn by calling dealerTurn().
        }

        updateGameOutcome(gambleAmount); // The game outcome is updated based on the results by calling updateGameOutcome(gambleAmount).
        endRound();
        printResult();
        printCurrency();
        updateRecord();
        // The round is ended by calling endRound().
        // The results of the round are printed by calling printResult().
        // The player's current currency is displayed by calling printCurrency().
        // The game record is updated by calling updateRecord().
        break;

      case 2: // Instructions and rules of the game are displayed.
        cout << "INSTRUCTIONS:\n" << endl;
        cout << "You must gain as much money as possible by beating the dealer "
                "by getting a count as close to 21 as"
             << endl;
        cout << "possible, without going over 21. \n" << endl;

        cout << "You will be dealt two cards, with the value of both cards "
                "being shown next to your hand"
             << endl;
        cout << "you will be then given a choice whether to hit, meaning you "
                "add another card to your hand, "
             << endl;
        cout << "or stand, meaning you keep your value \n" << endl;
        break;

      case 3: // The validChoice flag is set to true to exit the menu loop. 
            // The game ends.
        validChoice = true;
        cout << "Quitting the game..." << endl;
        return;
      default:
        cout << "Invalid choice! Please enter a valid option.\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

  } while (!validChoice);
    // After exiting the menu loop, the function checks if the player wants to play again.
  char playAgain = getPlayAgainDecision();
  if (playAgain != 'Y') {
    cout << "Quitting the game..." << endl;
    return; // If the player chooses not to play again, the game ends.
  }

  while (playAgain == 'Y') { // If the player chooses to play again, a new round starts.
    cout << "Enter the amount of money you want to gamble: "; // The player is prompted to enter the gambling amount.
    int gambleAmount;
    cin >> gambleAmount;
    playerCurrency -= gambleAmount; // The player's currency is updated, and input validation is performed.

    if (playerCurrency < 0) {
      cout << "You don't have enough money to gamble. Game over!" << endl;
      break;
    }
    // If the player chooses to play again, a new round starts.
    deck.shuffle();
    dealInitialCards();
    playerTurn(gambleAmount);
    if (!playerHand.isBust()) {
      dealerTurn();
    }
    updateGameOutcome(gambleAmount);
    endRound();

    printResult();
    printCurrency();

    char playAgainChoice;
    cout << "Would you like to play again? (Y/N): ";
    cin >> playAgainChoice;
    playAgain = toupper(playAgainChoice);
  }
}