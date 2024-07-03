#include "Deck.h"

// Deck constructor initializes a Deck object by populating its cards vector
// with Card objects representing a standard deck of playing cards
Deck::Deck() : size(0), capacity(52) {
    cards = new Card[capacity];
    for (int suit = HEARTS; suit <= SPADES; ++suit) {
        for (int rank = TWO; rank <= ACE; ++rank) {
            cards[size++] = Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }
}

Deck::~Deck() {
    delete[] cards;
}


// shuffle function iterates over the vector in reverse order and swaps each
// card with a randomly selected card from the remaining unshuffled portion of
// the deck This process results in a randomized order of the cards in the deck,
// simulating the act of shuffling a deck of playing cards


void Deck::shuffle() {
    for (int i = size - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}


// deal() function in the Deck class deals a Card object from the top of the
// deck by returning and removing the last Card object in the cards vector If
// the deck is empty, an exception is thrown to indicate that there are no more
// cards in the deck to be dealt
Card Deck::deal() {
    if (empty()) {
        throw out_of_range("No more cards in the deck!");
    }
    return cards[--size];
}
// Checks if the vector of cards is epmty, returns true: if the vector is empty,
// otherwise returns false

bool Deck::empty() const { return size == 0; }