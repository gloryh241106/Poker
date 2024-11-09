#include <iostream>
#include <vector>

#include "Engine/Game.h"
#include "Engine/Hand.h"
#include "Engine/PokerEngine.h"
#include "Engine/XiDachEngine.h"

int main() {
    std::cout << "\n";
    std::cout << "  ____ _               _                    _             \n";
    std::cout << " / ___| | __ _ ___ ___(_) ___   _ __   ___ | | _____ _ __ \n";
    std::cout
        << "| |   | |/ _` / __/ __| |/ __| | '_ \\ / _ \\| |/ / _ \\ '__|\n";
    std::cout
        << "| |___| | (_| \\__ \\__ \\ | (__  | |_) | (_) |   <  __/ |   \n";
    std::cout
        << " \\____|_|\\__,_|___/___/_|\\___| | .__/ \\___/|_|\\_\\___|_|   \n";
    std::cout << "                               |_|                        \n";
    std::cout << "\n";

    // initDeck(deck);

    std::cout << "What do you want to do?\n";
    std::cout << "1. New game\n";
    std::cout << "2. Load game\n";

    std::cout << randomName() << std::endl;

    int n;
    std::cout << "How much player do you want: ";
    std::cin >> n;
    if (n > 10) {
        std::cout << "That's too much!!!\n";
        return 0;
    }

    std::vector<Hand> players(n);

    Deck deck;
    for (int i = 0; i < 5; i++) {
        for (Hand &player : players) {
            player.add(deck.top());
            deck.pop();
        }
    }
    std::vector<std::pair<int, int>> evaluation;
    for (Hand &player : players) {
        evaluation.push_back(PokerEngine::evalPoker(player));
    }

    // TODO: This is for ranking players.
    std::vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return evaluation[a].first < evaluation[b].first ||
               (evaluation[a].first == evaluation[b].first &&
                evaluation[a].second < evaluation[b].second);
    });

    std::cout << "Ranking: \n";
    for (int id : idx) {
        std::cout << "Player " << id + 1 << " hand: " << players[id].toString()
                  << ", type: " << evaluation[id].first << std::endl;
    }
    return 0;
}