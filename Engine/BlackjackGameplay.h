#ifndef BLACKJACKGAMEPLAY_H
#define BLACKJACKGAMEPLAY_H

#include "BlackjackEngine.h"
#include "CLI.h"
#include "Player.h"
#include "deque_helper.h"

void xiDachGameRound(std::vector<Player>& player,
                     std::deque<int>& playerOrder) {
    int playerCount = playerOrder.size();

    // Increase bet if fewer player left
    int bet = (player.size() - playerCount + 1) * 50;
    // Initialize deck
    Deck deck;

    // Deal cards
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].hand.add(deck.draw());
        player[playerOrder.front()].hand.add(deck.draw());
        dequeNext(playerOrder);
    }

    int pot = 0;
    // Collect pot
    for (int i = 0; i < playerCount; i++) {
        player[playerOrder.front()].chips -= bet;
        pot += bet;
        dequeNext(playerOrder);
    }

    std::vector<std::pair<int, int>> blackjackEvals(player.size());

    // Eval
    for (int i = 0; i < playerCount; i++) {
        blackjackEvals[playerOrder.front()] =
            XiDachEngine::evalXiDach(player[playerOrder.front()].hand);
        dequeNext(playerOrder);
    }

    // Xi ban, xi dach
    int xiBanCount = 0;
    int xiDachCount = 0;

    // Pre evaluation
    for (int i = 0; i < playerCount; i++) {
        if (blackjackEvals[playerOrder.front()].first == XiDachHandType::XI_BAN)
            xiBanCount++;
        else if (blackjackEvals[playerOrder.front()].first ==
                 XiDachHandType::XI_DACH)
            xiDachCount++;
        dequeNext(playerOrder);
    }

    // Xi ban insta-win
    if (xiBanCount) {
        for (int i = 0; i < playerCount; i++) {
            if (blackjackEvals[playerOrder.front()].first ==
                XiDachHandType::XI_BAN) {
                std::cout << "Player " << playerOrder.front() << " wins."
                          << std::endl;
                std::cout << player[playerOrder.front()].hand.toString()
                          << XiDachEngine::type(
                                 blackjackEvals[playerOrder.front()])
                          << std::endl;
                player[playerOrder.front()].chips += pot / xiBanCount;
            }
            dequeNext(playerOrder);
        }
        return;
    }

    // Xi dach insta-win
    if (xiDachCount) {
        for (int i = 0; i < playerCount; i++) {
            if (blackjackEvals[playerOrder.front()].first ==
                XiDachHandType::XI_DACH) {
                std::cout << "Player " << playerOrder.front() << " wins."
                          << std::endl;
                std::cout << player[playerOrder.front()].hand.toString()
                          << XiDachEngine::type(
                                 blackjackEvals[playerOrder.front()])
                          << std::endl;
                player[playerOrder.front()].chips += pot / xiDachCount;
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
            std::cout << player[playerOrder.front()].hand.toString()
                      << std::endl;
            std::cout << "Do you want to draw? ";
            bool userChoice = CLI::getOptionYN();
            if (!userChoice) break;
            player[playerOrder.front()].hand.add(deck.draw());
            blackjackEvals[playerOrder.front()] =
                XiDachEngine::evalXiDach(player[playerOrder.front()].hand);
            if (blackjackEvals[playerOrder.front()].first ==
                XiDachHandType::QUAC)
                break;
        }
    }

    // Showdown
    std::vector<int> playerRank(playerOrder.begin(), playerOrder.end());
    std::sort(playerRank.begin(), playerRank.end(), [&](int a, int b) {
        return blackjackEvals[a].first > blackjackEvals[b].first ||
               (blackjackEvals[a].first == blackjackEvals[b].first &&
                blackjackEvals[a].second > blackjackEvals[b].second);
        ;
    });

    // Display the hands
    CLI::clearScreen();
    std::cout << "Showdown" << std::endl;
    for (int i = 0; i < playerCount; i++) {
        if (player[playerRank[i]].folded) continue;
        std::cout << "Player " << playerRank[i]
                  << "'s hand: " << player[playerRank[i]].hand.toString() << ' '
                  << XiDachEngine::type(blackjackEvals[playerRank[i]])
                  << std::endl;
    }

    // Divide pot
    std::pair<int, int> best = blackjackEvals[playerRank[0]];
    int countBest = 1;
    for (int i = 1; i < playerCount; i++) {
        if (blackjackEvals[playerRank[i]] == best) countBest++;
    }
    for (int i = 1; i < playerCount; i++) {
        if (blackjackEvals[playerRank[i]] == best) {
            player[playerRank[i]].chips += pot / countBest;
        }
    }

    // Display the chips
    for (int i = 0; i < playerCount; i++) {
        std::cout << "Player " << i << " has " << player[i].chips << " chips"
                  << std::endl;
    }

    // Remove lost players
    int i = 0;
    while (i < playerOrder.size()) {
        if (player[playerOrder.front()].chips == 0) {
            player[playerOrder.front()].lost = 1;
            playerOrder.pop_front();
            continue;
        }

        dequeNext(playerOrder);
        i++;
    }
}

#endif  // BLACKJACKGAMEPLAY_H