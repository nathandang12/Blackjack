#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "Card.h"
#include "Deck.h"
#include "BaseHand.h"
#include "Hand.h"
#include "BlackjackHand.h"
#include "BlackjackGame.h"


using namespace std;


// Function to generate random numbers in a range
int random(int min, int max) { return rand() % (max - min + 1) + min; }

// getInput function: repeatedly prompts the user to enter a number within a
// specific range until a valid input is received. It handles invalid inputs and
// ensures that only valid values are returned.
int getInput(int min, int max) {
  int input;
  while (!(cin >> input) || input < min || input > max) {
    cout << "Invalid input! Please enter a number between " << min << " and "
         << max << ": ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return input;
}


int main() {
  BlackjackGame game;
  game.play();

  return 0;
}