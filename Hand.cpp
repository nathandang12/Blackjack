#include "Hand.h"


Hand::Hand() : value(0), soft(false), size(0), capacity(10) {
    cards = new Card[capacity];
}

Hand::~Hand() {
    delete[] cards;
}


// The add function efficiently handles the addition of cards to the hand, dynamically resizing the cards array when necessary and updating the hand's value and soft flag accordingly.
void Hand::add(const Card &card) {
    if (size >= capacity) { // If the current number of cards in the hand (size) >= the cards array, capacity doubles. ensures cards array has enough space to accommodate the new card.
        capacity *= 2;
    // A new dynamically allocated array called newCards is created with the updated capacity. 
    // The elements from the old cards array are copied to the new array.
        Card* newCards = new Card[capacity]; 

        for (int i = 0; i < size; ++i) {
            newCards[i] = cards[i];
        }
    
        delete[] cards;
        cards = newCards;
    }
    // If the added card is an ACE, it checks if the current value of the hand (value) is less than or equal to 10. 
    // If so, adding the ACE as 11 would not cause the hand to exceed 21, so the value is incremented by 11 and the soft flag is set to true. 
    // Otherwise, the ACE is added as 1 to prevent the hand from exceeding 21.
    
    cards[size++] = card; 
    if (card.getRank() == ACE) {
        if (value <= 10) {
            value += 11;
            soft = true;
        } else {
            value += 1;
        }
    // If the added card is not an ACE, its value is obtained using the getValue function of the Card class, and the value of the hand is incremented by the card's value.
    } else {
        value += card.getValue();
        if (value > 21 && soft) {
            value -= 10;
            soft = false;
        }
    }
}

// By deleting the old cards array, creating a new empty array, and resetting the member variables, 
// the clear function effectively clears the hand, preparing it for a new round or a fresh set of cards.
void Hand::clear() {
    delete[] cards;
    cards = new Card[capacity];
    size = 0;
    value = 0;
    soft = false;
}

// the operator<< overload for the Hand class allows a Hand object to be printed
// to the output stream (cout). It prints each card in the hand, separated by
// spaces, and appends the value of the hand within parentheses. The function
// facilitates easy and customizable printing of a Hand object.
ostream &operator<<(ostream &os, const Hand &hand) {
    for (int i = 0; i < hand.getCardCount(); ++i) {
        os << hand.getCards()[i] << " ";
    }
    os << " (" << hand.getValue() << ")";
    return os;
}

// the display() function in the Hand class prints the label "Hand: " followed
// by the representation of the Hand object using the overloaded operator<< for
// the Hand class. This function provides a convenient way to display the
// contents of a Hand object, typically used in debugging or user interface
// scenarios.
void Hand::display() const { cout << "Hand: " << *this << endl; }