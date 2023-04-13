#include <iostream>
#include <iomanip>
#include "player.hpp"

namespace ariel {
    Player::Player(std::string _name) {
        
        name = _name;
        winCount = 0;
        loseCount = 0;
        drawCount = 0;
    }

    int Player::stacksize() const {
        return handplay.size();
    }

    int Player::cardesTaken() {
        return EarnedCards.size();
    }

    void Player::setName(std::string n) {
        name = n;
    }

    std::string Player::getName() {
        return name;
    }

    void Player::setCardPlay(card c) {
        handplay.push_back(c);
    }

    void Player::setCardEarn(card c) {
        EarnedCards.push_back(c);
        calculateStatistics(getDeckEarn());
    }

    card Player::getCardPlay() {
        card c = handplay.back();
        handplay.pop_back();
        return c;
    }

    std::vector<card> Player::getDeckEarn() {
        return EarnedCards;
    }

    std::vector<card> Player::getDeckPlay() {
        return handplay;
    }

    void Player::updateDeckPlay(std::vector<card> cards) {
        handplay = cards;
    }

    bool Player::deckPlayNOTempty() {
        return !handplay.empty();
    }

    int Player::getWinCount() const {
        return winCount;
    }

    int Player::getLoseCount() const {
        return loseCount;
    }

    int Player::getDrawCount() const {
        return drawCount;
    }

    void Player::incrementWinCount() {
        winCount++;
    }

    void Player::incrementLoseCount() {
        loseCount++;
    }

    void Player::incrementDrawCount() {
        drawCount++;
    }
    
std::string Player::calculateStatistics(const std::vector<card>& deckEarn) {
    
    for (card c : deckEarn) {
        if (c.getNumber() > 0) { // player won
            incrementWinCount();
        } else if (c.getNumber() < 0) { // player lost
            incrementLoseCount();
        } else { // draw
            incrementDrawCount();
        }
    }

    double totalGames = getWinCount() + getLoseCount() + getDrawCount();

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    if (totalGames > 0) {
        double winPercentage = (getWinCount() / totalGames) * 100;
        double losePercentage = (getLoseCount() / totalGames) * 100;
        double drawPercentage = (getDrawCount() / totalGames) * 100;

        stream << "Win percentage: " << winPercentage << "%" << std::endl;
        stream << "Lose percentage: " << losePercentage << "%" << std::endl;
        stream << "Draw percentage: " << drawPercentage << "%" << std::endl;
    } else {
        stream << "No games played yet" << std::endl;
    }

    return stream.str();
}



}
