#ifndef __GAME__
#define __GAME__

#include <string>

#include "Hand.h"
#include "PokerEngine.h"
#include "Random.h"
#include "XiDachEngine.h"

// Generate a random player name
std::string randomName() {
    std::string alphaNumeric =
        "01233456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::shuffle(alphaNumeric.begin(), alphaNumeric.end(), globalRNG);
    return "Player " + alphaNumeric.substr(0, 10);
}

enum GameType {
    POKER = 0,
    XIDACH,
};

enum PlayerAction {
    FOLD,
    BET,
    RAISE,
    ALL_IN,
};

class Player {
   public:
    std::string name;
    int points;
    Hand hand;
    bool folded = 0;
    bool isHuman = 0;
    GameType game;

    Player(GameType game, int initialPoints)
        : game(game), name(randomName()), points(initialPoints) {}

    Player(GameType game, const std::string& playerName, int initialPoints)
        : game(game), name(playerName), points(initialPoints) {}

    // Decide whether to raise or fold based on the hand
    bool shouldRaise() {
        auto evaluation = PokerEngine::evalPoker(hand);
        int handType = evaluation.first;

        // Raise if the hand is at least a pair
        if (handType >= HandType::ONE_PAIR) {
            return true;
        }
        return false;
    }

    // Place a bet
    bool placeBet(int betAmount) {
        if (betAmount > points) {
            return false;  // Not enough points to place the bet
        }
        points -= betAmount;
        return true;
    }

    // TODO: Poker AI
    std::pair<PlayerAction, int> getPlayerAction(const int& minBet) {}

    // Fold
    void fold() { folded = true; }
};

class Game {
   public:
    int playerCount;
    Deck deck;
    GameType game;
    int minBet = 10;
    // The zero index player is the Human player
    int playerOrder[10]{};
    std::vector<Player> players;
    Game(int playerCount, GameType game)
        : players(std::vector(playerCount, Player(game, 1000))),
          playerCount(playerCount),
          deck(Deck()),
          game(game) {
        for (int i = 0; i < playerCount; i++) playerOrder[i] = i;
    }

    // Generate a new game
    void newGame(int count = -1) {
        if (count != -1) {
            playerCount = count;
            for (int i = 0; i < playerCount; i++) playerOrder[i] = i;
        }
        minBet = 10;
        deck.newDeck();
    }

    // Deal one card for each player
    void dealRound() {
        for (int i = 0; i < playerCount; i++)
            players[playerOrder[i]].hand.add(deck.top());
        deck.pop();
    }

    // Ask each player whether they want to bet, raise or fold
    void betRound() {
        for (int i = 0; i < playerCount; i++) {
            // Skip folded players
            if (players[playerOrder[i]].folded) continue;
            if (playerOrder[i] == 0) {  // Human player
            }
        }
    }

    // TODO: Load game
    // TODO: Save game
};

#endif