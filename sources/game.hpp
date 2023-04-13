#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.hpp"
#include "card.hpp"

namespace ariel {

    class Game {
    private:
        Player &player1, &player2;
        std::vector<card> Deck;
        int countTurn;//for the game statics
        std::string turnstatics;
        std::vector<std::string> gamestatics;


    public:
        Game(Player& pl1, Player& pl2);

        void playAll();
        void printWiner(); 
        void printLog();
        void printStats();
        void playTurn();
        void printLastTurn();
        void createDeck();
        void shuffleDeck();
        std::vector<card> getDeck();
        void dealingCards();

    };
}

#endif
