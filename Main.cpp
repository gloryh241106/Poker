#include <iostream>
#include <vector>

#include "Engine/Gameplay/Hand.h"

int main() {
    std::cout << "Welcome to Poker!" << std::endl;

    // initDeck(deck);

    int n;
    std::cout << "How much player do you want: ";
    std::cin >> n;
    if (n > 10) {
        std::cout << "That's too much!!!" << std::endl;
        return 0;
    }

    std::vector<Hand> players(n);
    // divideCards(players, n);
    // displayHands(players, n);
    // setRankingMatch(players);
    // displayLeaderboard(players);

    std::vector<int> deck = generateDeck();
    for (int i = 0; i < 5; i++) {
        for (Hand &player : players) {
            player.add(deck.back());
            deck.pop_back();
        }
    }
    std::vector<std::pair<int, int>> evaluation;
    for (Hand &player : players) {
        evaluation.push_back(evalPoker(player));
    }

    // TODO: This is for ranking players.
    std::vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return evaluation[a].first < evaluation[b].first ||
               (evaluation[a].first == evaluation[b].first &&
                evaluation[a].second < evaluation[b].second);
    });

    std::cout << "Ranking: " << std::endl;
    for (int id : idx) {
        std::cout << "Player " << id + 1 << " hand: " << players[id].toString()
                  << ", type: " << evaluation[id].first << std::endl;
    }
    return 0;
}