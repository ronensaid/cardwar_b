#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "card.hpp"

namespace ariel {

    class Player {
    private:
        std::string name;
        std::vector<card> handplay;
        std::vector<card> EarnedCards;
        int winCount, loseCount, drawCount;

    public:
        Player(std::string _name);

        int stacksize() const;
        int cardesTaken();
        void setName(std::string n);
        std::string getName();
        void setCardPlay(card);
        void setCardEarn(card);
        card getCardPlay();
        std::vector<card> getDeckEarn();
        std::vector<card> getDeckPlay();
        void updateDeckPlay(std::vector<card>);
        bool deckPlayNOTempty();
        int getWinCount() const;
        int getLoseCount() const;
        int getDrawCount() const;
        void incrementWinCount();
        void incrementLoseCount();
        void incrementDrawCount();

        // Function declaration for calculateStatistics
        std::string calculateStatistics(const std::vector<card>& deckEarn);
    };
}

#endif
