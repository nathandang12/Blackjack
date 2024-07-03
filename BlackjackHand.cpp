#include "BlackjackHand.h"

bool BlackjackHand::isBlackjack() const {
  return (getValue() == 21);
}

bool BlackjackHand::isBust() const {
  return (getValue() > 21);
}

bool BlackjackHand::isFiveCardCharlie() const {
  return (getSize() == 5 && getValue() <= 21);
}
