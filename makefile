# Default target
all: blackjack_game

# Build the executable
blackjack_game: main.cpp Card.cpp Deck.cpp Hand.cpp BlackjackGame.cpp BlackjackHand.cpp BaseHand.cpp
	g++ -std=c++11 -Wall -Wextra -Werror main.cpp Card.cpp Deck.cpp Hand.cpp BlackjackGame.cpp BlackjackHand.cpp BaseHand.cpp -o blackjack_game

# Compile source files
%.o: %.cpp
	g++ -std=c++11 -Wall -Wextra -Werror -c $< -o $@

# Debug build
debug: -std=c++11 -Wall -Wextra -Werror += -g -DDEBUG
debug: clean all

# Release build
release: -std=c++11 -Wall -Wextra -Werror += -O2
release: clean all

# Clean build files
clean:
	rm -f main.cpp Card.cpp Deck.cpp Hand.cpp BlackjackGame.cpp blackjack_game