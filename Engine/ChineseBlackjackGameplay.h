#ifndef CHINESEPOKERGAMEPLAY_H
#define CHINESEPOKERGAMEPLAY_H

#include "ChineseBlackjackEngine.h"
#include "CLI.h"
#include "Player.h"
#include "deque_helper.h"

void ChineseBlackjackGameRound(std::vector<Player>& players, std::deque<int>& playerOrder) {
    int playerCount = playerOrder.size();

    // Increase bet if fewer player left
    int bet = (players.size() - playerCount + 1) * 50;
    // Initialize deck
    Deck deck;

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        players[playerOrder.front()].hand.add(deck.draw());
        players[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    int pot = 0;
    // Collect pot
    for (int i = 0; i < playerCount; i++) {
        players[playerOrder.front()].chips -= bet;
        pot += bet;
        dequeNext(playerOrder);
    }

    std::vector<std::pair<int, int>> chinesePokerEvals(players.size());

    // Eval
    for (int i = 0; i < playerCount; i++) {
        chinesePokerEvals[playerOrder.front()] = ChineseBlackjackEngine::evalChineseBlackjack(players[playerOrder.front()].hand);
        dequeNext(playerOrder);
    }

    // Xi ban, xi dach
    int xiBanCount = 0;
    int xiDachCount = 0;

    // Pre evaluation
    for (int i = 0; i < playerCount; i++) {
        if (chinesePokerEvals[playerOrder.front()].first == ChineseBlackjackHandType::XI_BAN)
            xiBanCount++;
        else if (chinesePokerEvals[playerOrder.front()].first == ChineseBlackjackHandType::XI_DACH)
            xiDachCount++;
        dequeNext(playerOrder);
    }

    // Xi ban insta-win
    if (xiBanCount) {
        for (int i = 0; i < playerCount; i++) {
            if (chinesePokerEvals[playerOrder.front()].first ==
                ChineseBlackjackHandType::XI_BAN) {
                std::cout << "Player " << playerOrder.front() << " wins."
                          << std::endl;
                std::cout << players[playerOrder.front()].hand.toString()
                          << ChineseBlackjackEngine::type(chinesePokerEvals[playerOrder.front()])
                          << std::endl;
                players[playerOrder.front()].chips += pot / xiBanCount;
            }
            dequeNext(playerOrder);
        }

        return;
    }

    // Xi dach insta-win
    if (xiDachCount) {
        for (int i = 0; i < playerCount; i++) {
            if (chinesePokerEvals[playerOrder.front()].first == ChineseBlackjackHandType::XI_DACH) {
                std::cout << "Player " << playerOrder.front() << " wins."
                          << std::endl;
                std::cout << players[playerOrder.front()].hand.toString()
                          << ChineseBlackjackEngine::type(chinesePokerEvals[playerOrder.front()])
                          << std::endl;
                players[playerOrder.front()].chips += pot / xiDachCount;
            }
            dequeNext(playerOrder);
        }

        return;
    }

    // Deal card
    for (int i = 0; i < playerCount; i++) {
        std::cout << "Player " << playerOrder.front()
                  << "'s hand:" << std::endl;
        for (int j = 0; j < 3; j++) {
            std::cout << players[playerOrder.front()].hand.toString() << std::endl;
            std::cout << "Do you want to draw? ";
            bool userChoice = CLI::getOptionYN();

            if (!userChoice) break;
            players[playerOrder.front()].hand.add(deck.draw());
            chinesePokerEvals[playerOrder.front()] = ChineseBlackjackEngine::evalChineseBlackjack(players[playerOrder.front()].hand);
            if (chinesePokerEvals[playerOrder.front()].first == ChineseBlackjackHandType::QUAC) {
                std::cout << "Player " << playerOrder.front() << "'s hand:" << std::endl;
                std::cout << players[playerOrder.front()].hand.toString() << std::endl;
                CLI::getEnter();
                break;
            }
        }

        CLI::clearScreen();
        dequeNext(playerOrder);
        CLI::sleep(2000);
    }

    // Showdown
    std::vector<int> playerRank(playerOrder.begin(), playerOrder.end());
    std::sort(playerRank.begin(), playerRank.end(), [&](int a, int b) {
        return chinesePokerEvals[a].first > chinesePokerEvals[b].first ||
               (chinesePokerEvals[a].first == chinesePokerEvals[b].first &&
                chinesePokerEvals[a].second > chinesePokerEvals[b].second);
        ;
    });

    // Display the hands
    CLI::clearScreen();
    std::cout << "Showdown" << std::endl;
    for (int i = 0; i < playerCount; i++) {
        if (players[playerRank[i]].folded) continue;
        std::cout << "Player " << playerRank[i]
                  << "'s hand: " << players[playerRank[i]].hand.toString() << ' '
                  << ChineseBlackjackEngine::type(chinesePokerEvals[playerRank[i]])
                  << std::endl;
    }

    // Divide pot
    std::pair<int, int> best = chinesePokerEvals[playerRank[0]];
    int countBest = 1;
    for (int i = 1; i < playerCount; i++) {
        if (chinesePokerEvals[playerRank[i]] == best) countBest++;
    }
    for (int i = 1; i < playerCount; i++) {
        if (chinesePokerEvals[playerRank[i]] == best) {
            players[playerRank[i]].chips += pot / countBest;
        }
    }

    // Display the chips
    for (int i = 0; i < playerCount; i++) {
        std::cout << "Player " << i << " has " << players[i].chips << " chips" << std::endl;
    }

    // Remove lost players
    int i = 0;
    while (i < playerOrder.size()) {
        if (players[playerOrder.front()].chips == 0) {
            players[playerOrder.front()].lost = 1;
            playerOrder.pop_front();
            continue;
        }

        dequeNext(playerOrder);
        i++;
    }
}

#endif  // CHINESEPOKERGAMEPLAY_H