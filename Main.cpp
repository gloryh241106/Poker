#include <chrono>
#include <deque>
#include <iostream>
#include <thread>
#include <vector>

#include "Engine/CLI.h"
#include "Engine/Card.h"
#include "Engine/Random.h"
// #include "Engine/Game.h"
#include "Engine/Hand.h"
#include "Engine/PokerEngine.h"
// #include "Engine/XiDachEngine.h"

enum PlayerAction { NONE, CHECK, CALL, BET, RAISE, FOLD, ALL_IN };

struct Player {
    Hand hand;
    std::string name;
    int chips;
    int bet;
    bool folded;
    bool lost;
    bool allIn;
    PlayerAction action = NONE;
    int showdownBet = 0;
};

void dequeNext(std::deque<int>& q) {
    int front = q.front();
    q.pop_front();
    q.push_back(front);
}

void dequePrev(std::deque<int>& q) {
    int back = q.back();
    q.pop_back();
    q.push_front(back);
}

PlayerAction askPlayerAction(Player& player, const int& currBet,
                             const int& minRaiseDiff, bool& preflop) {
    if (currBet == 0) {
        std::cout << "1. Check" << std::endl;
        std::cout << "2. Raise" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);
        if (op == 1) {
            return PlayerAction::CHECK;
        } else if (op == 2) {
            preflop = false;
            return PlayerAction::RAISE;
        } else {
            return PlayerAction::FOLD;
        }
    } else if (currBet >= player.chips) {
        std::cout << "1. All In" << std::endl;
        std::cout << "2. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 2);
        if (op == 1) {
            return PlayerAction::ALL_IN;
        } else {
            return PlayerAction::FOLD;
        }
    } else if (currBet + minRaiseDiff >= player.chips) {
        std::cout << "1. Call" << std::endl;
        std::cout << "2. All In" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);
        if (op == 1) {
            return PlayerAction::CALL;
        } else if (op == 2) {
            return PlayerAction::ALL_IN;
        } else {
            return PlayerAction::FOLD;
        }
    } else {
        std::cout << "1. Call" << std::endl;
        std::cout << "2. Raise" << std::endl;
        std::cout << "3. Fold" << std::endl;
        int op = CLI::getOptionNum(1, 3);
        if (op == 1) {
            return PlayerAction::CALL;
        } else if (op == 2) {
            return PlayerAction::RAISE;
        } else {
            return PlayerAction::FOLD;
        }
    }
    return PlayerAction::NONE;
}

// https://en.wikipedia.org/wiki/Betting_in_poker
// Returns the index of the player who won the round
// Otherwise returns -1
int drawPokerBetRound(std::vector<Player>& player, std::deque<int> playerOrder,
                      int blind, bool preflop, int& pot) {
    int playerCount = player.size();
    int playerInGame = playerOrder.size();

    if (playerInGame < 1) {
        return -1;
    }

    // Check if there is only one player left
    if (playerInGame == 1) {
        return playerOrder.front();
    }

    // Forced bets
    bool forcedBet = 0;
    if (preflop) {
        forcedBet = 1;
        if (playerInGame == 2) {
            player[playerOrder.front()].bet += blind;  // Small blind
            dequeNext(playerOrder);
            player[playerOrder.front()].bet += blind * 2;  // Big blind
        } else {
            dequeNext(playerOrder);
            player[playerOrder.front()].bet += blind;  // Small blind
            dequeNext(playerOrder);
            player[playerOrder.front()].bet += blind * 2;  // Big blind
        }
    }

    int currBet = preflop ? blind * 2 : 0;

    int minRaiseDiff = preflop ? blind * 2 : 0;

    // If preflop, the player after the big blind is the first to act
    // Else, the dealer is the first to act
    int raisedPlayer = playerOrder.front();

    bool live = 1;  // The betting round is live
    while (live) {
        live = false;
        do {
            dequeNext(playerOrder);

            // Skip players who have folded
            if (player[playerOrder.front()].folded) {
                // dequeNext(playerOrder);
                continue;
            }

            // DRAW POKER ONLY -------------------------------------------------

            std::cout << "\n\n";  // CLI::clearScreen();
            for (int i : playerOrder) {
                std::cout << "Player's " << i
                          << " hand: " << player[i].hand.toString(1)
                          << std::endl;
            }

            //------------------------------------------------------------------

            std::cout << "\n\n";  // CLI::clearScreen();
            std::cout << "Player " << playerOrder.front() << "'s turn "
                      << std::endl;
            //   << betPlayerCount
            std::cout << "Your hand: "
                      << player[playerOrder.front()].hand.toString()
                      << std::endl;
            std::cout << "Your remaining chips: "
                      << player[playerOrder.front()].chips << std::endl;
            std::cout << "You bet: " << player[playerOrder.front()].bet
                      << std::endl;
            std::cout << "Pot: " << pot << std::endl;

            if (player[playerOrder.front()].allIn) {
                std::cout << "You have gone all in" << std::endl;
                CLI::getEnter();
                if (playerOrder.front() == raisedPlayer) {
                    break;
                } else {
                    // dequeNext(playerOrder);
                    continue;
                }
            }

            std::cout << "Current bet amount: " << currBet << std::endl;
            std::cout << "What do you want to do?" << std::endl;

            PlayerAction op = askPlayerAction(player[playerOrder.front()],
                                              currBet, minRaiseDiff, preflop);

            std::cout << std::endl;

            if (op == PlayerAction::CHECK ||
                op == PlayerAction::CALL) {  // CHECK/CALL
                player[playerOrder.front()].bet = currBet;

                if (player[playerOrder.front()].chips <= currBet) {  // ALL IN
                    player[playerOrder.front()].allIn = 1;
                    player[playerOrder.front()].bet =
                        player[playerOrder.front()].chips;
                }

                // if (playerOrder.front() == raisedPlayer) {
                //     break;
                // } else {
                //     dequeNext(playerOrder);
                //     continue;
                // }
            } else if (op == PlayerAction::BET) {
                std::cout << "How much do you want to bet?" << std::endl;
                int bet = CLI::getOptionNum(blind * 2,
                                            player[playerOrder.front()].chips);
                minRaiseDiff = bet - currBet;
                currBet = bet;
                player[playerOrder.front()].bet = currBet;
                if (currBet == player[playerOrder.front()].chips) {  // ALL IN
                    player[playerOrder.front()].allIn = 1;
                }
                live = true;
                raisedPlayer = playerOrder.front();
            } else if (op == PlayerAction::RAISE) {
                std::cout << "Min raise: " << currBet + minRaiseDiff
                          << std::endl;
                std::cout << "How much do you want to raise to?" << std::endl;
                int raise = CLI::getOptionNum(
                    currBet + minRaiseDiff, player[playerOrder.front()].chips);
                minRaiseDiff = raise - currBet;
                currBet = raise;
                player[playerOrder.front()].bet = currBet;
                if (currBet >= player[playerOrder.front()].chips) {  // ALL IN
                    player[playerOrder.front()].allIn = 1;
                }
                live = true;
                raisedPlayer = playerOrder.front();
            } else if (op == PlayerAction::ALL_IN) {  // ALL IN
                player[playerOrder.front()].allIn = 1;
                player[playerOrder.front()].bet =
                    player[playerOrder.front()].chips;
                int diff = player[playerOrder.front()].chips - currBet;
                currBet = std::max(currBet, player[playerOrder.front()].bet);
                // If the player goes all-in, others are only allowed to
                // re-raise if he exceeds the minimum raise.
                if (diff > minRaiseDiff) {
                    minRaiseDiff = diff;
                    live = true;
                    raisedPlayer = playerOrder.front();
                }
            } else if (op == PlayerAction::FOLD) {  // FOLD
                player[playerOrder.front()].folded = 1;
                playerInGame--;
            }
            // Check if there is only one player left
            if (playerInGame == 1) {
                for (int i = 0; i < playerCount; i++) {
                    if (!player[i].folded) {
                        return i;
                    }
                }
            }
            // dequeNext(playerOrder);
        } while (playerOrder.front() != raisedPlayer);
    }

    // Collect the pot
    for (int i : playerOrder) {
        pot += player[i].bet;
        player[i].showdownBet += player[i].bet;
        player[i].chips -= player[i].bet;
        player[i].bet = 0;
    }

    return -1;
}

void showdown(std::vector<Player>& player, std::deque<int>& playerOrder,
              int& pot) {
    // int pot = 0;
    int playerCount = playerOrder.size();
    for (int i : playerOrder) {
        // std::cout << "Here " << p.bet << std::endl;
        // CLI::getEnter();
        // pot += p.bet;
        // p.chips -= p.bet;
        if (player[i].folded) continue;
        PokerEngine::eval(player[i].hand.bit());
    }

    std::vector<int> playerRank(playerOrder.begin(), playerOrder.end());

    // Sort the players by hand strength
    std::sort(playerRank.begin(), playerRank.end(), [&](int a, int b) {
        return PokerEngine::compareHands(player[a].hand, player[b].hand);
    });

    // Display the hands
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Showdown" << std::endl;
    for (int i = 0; i < playerCount; i++) {
        if (player[playerRank[i]].folded) continue;
        std::cout << "Player " << playerRank[i]
                  << "'s hand: " << player[playerRank[i]].hand.toString()
                  << " (" << PokerEngine::type(player[playerRank[i]].hand)
                  << ")" << std::endl;
    }
    for (int i : playerRank) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    // Distribute the pot
    int i = 0;
    while (i < playerCount && pot > 0) {
        player[playerRank[i]].showdownBet = std::min(
            pot, player[playerRank[i]].showdownBet * (playerCount - i));
        player[playerRank[i]].chips += player[playerRank[i]].showdownBet;
        pot -= std::min(pot,
                        player[playerRank[i]].showdownBet * (playerCount - i));
        i--;
    }

    // Display the chips
    for (int i = 0; i < playerCount; i++) {
        std::cout << "Player " << i << " has " << player[i].chips << " chips"
                  << std::endl;
    }

    // Remove lost players
    i = 0;
    while (i < playerOrder.size()) {
        if (player[playerOrder.front()].chips == 0) {
            player[playerOrder.front()].lost = 1;
            playerOrder.pop_front();
            continue;
        }
        dequeNext(playerOrder);
        i++;
    }

    // Reset the players
    for (int i : playerOrder) {
        player[i].hand.clear();
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].allIn = 0;
        player[i].showdownBet = 0;
    }
    CLI::getEnter();
}

void lastPlayerStanding(std::vector<Player>& player,
                        std::deque<int>& playerOrder, int lastPlayer,
                        int& pot) {
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Player " << lastPlayer << " wins the round" << std::endl;
    player[lastPlayer].chips += pot;
    CLI::getEnter();

    // Reset the players
    for (int i : playerOrder) {
        player[i].hand.clear();
        player[i].bet = 0;
        player[i].folded = 0;
        player[i].allIn = 0;
        player[i].showdownBet = 0;
    }
}

void drawPokerGameRound(std::vector<Player>& player,
                        std::deque<int>& playerOrder, int blind) {
    int playerCount = playerOrder.size();

    // Initialize deck
    Deck deck;

    int pot = 0;
    // int dealerIndex = 0;

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Pre-flop ----------------------------------------------------------------
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Pre-flop" << std::endl;
    CLI::sleep(1000);
    int lastPlayer = drawPokerBetRound(player, playerOrder, blind, 1, pot);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Flop --------------------------------------------------------------------
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Flop" << std::endl;
    CLI::sleep(1000);
    lastPlayer = drawPokerBetRound(player, playerOrder, blind, 0, pot);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // Turn --------------------------------------------------------------------
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "Turn" << std::endl;
    CLI::sleep(1000);
    lastPlayer = drawPokerBetRound(player, playerOrder, blind, 0, pot);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    // River -------------------------------------------------------------------
    std::cout << "\n\n";  // CLI::clearScreen();
    std::cout << "River" << std::endl;
    CLI::sleep(1000);
    lastPlayer = drawPokerBetRound(player, playerOrder, blind, 0, pot);

    // Player wins because everyone else folded
    if (lastPlayer != -1) {
        lastPlayerStanding(player, playerOrder, lastPlayer, pot);
        return;
    }
    //--------------------------------------------------------------------------

    // Showdown
    showdown(player, playerOrder, pot);
}

int main() {
    bool exited = 0;
    while (!exited) {
        std::cout << "\n\n";  // CLI::clearScreen();
        CLI::title();

        int op = 0;
        std::cout << std::endl;
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1. New game" << std::endl;
        std::cout << "0. Exit" << std::endl;
        op = CLI::getOptionNum(0, 1);

        if (op == 0) {
            exited = 1;
        } else if (op == 1) {
            std::cout << "\n\n";  // CLI::clearScreen();

            // Initialize players
            std::cout << "How many players do you want to play with?"
                      << std::endl;
            int playerCount = CLI::getOptionNum(2, 8);

            std::vector<Player> player(playerCount, Player());
            for (Player& p : player) {
                p.hand = Hand();
                p.name = Random::_name();
                p.chips = 1000;
                p.bet = 0;
                p.folded = 0;
                p.lost = 0;
                p.allIn = 0;
            }

            // Masking card
            for (int i = 0; i < playerCount; i++) {
                player[i].hand.setMask(0x01);
            }

            // Initialize player's order
            std::deque<int> playerOrder;
            for (int i = 0; i < playerCount; i++) {
                playerOrder.push_back(i);
            }
            drawPokerGameRound(player, playerOrder, 5);

            // Uncomment this to play multiple
            // rounds-- -- -- -- -- -- -- -- -- -- -- -- -- -
            //
            // int round = 1;
            // while (player.size() > 1) {
            //     std::cout << "\n\n"; // CLI::clearScreen();
            //     std::cout << "Round " << round << std::endl;
            //     CLI::sleep(1000);
            //     gameRound(player, playerOrder, 5);
            //     round++;
            // }
            //
            //------------------------------------------------------------------
        }
    }

    // Hand hand;
    // hand.add(Suit::SPADES | (Rank::TEN << 2));
    // hand.add(Suit::HEARTS | (Rank::TEN << 2));
    // hand.add(Suit::SPADES | (Rank::SIX << 2));
    // hand.add(Suit::CLUBS | (Rank::SIX << 2));
    // hand.add(Suit::CLUBS | (Rank::TEN << 2));
    // PokerEngine::eval(hand.bit());
    // std::cout << hand.toString() << std::endl;
    // std::cout << PokerEngine::type(hand) << std::endl;
    // std::cout << hand.bit() << std::endl;
    // std::cout << hand.compressedBit() << std::endl;

    // hand.clear();

    // hand.add(Suit::CLUBS | (Rank::SIX << 2));
    // hand.add(Suit::DIAMONDS | (Rank::SIX << 2));
    // hand.add(Suit::SPADES | (Rank::SIX << 2));
    // hand.add(Suit::DIAMONDS | (Rank::TEN << 2));
    // hand.add(Suit::CLUBS | (Rank::TEN << 2));
    // PokerEngine::eval(hand.bit());
    // std::cout << hand.toString() << std::endl;
    // std::cout << PokerEngine::type(hand) << std::endl;
    // std::cout << hand.bit() << std::endl;
    // std::cout << hand.compressedBit() << std::endl;
    return 0;
}
