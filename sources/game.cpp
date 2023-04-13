#include "game.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
using namespace ariel;

//Constructor
Game::Game(Player& pl1, Player& pl2): player1(pl1), player2(pl2), countTurn(0)
{
    createDeck(); 
    shuffleDeck(); 
    dealingCards(); 
}

vector<card> Game::getDeck()
{
    return Deck;
}

void Game::createDeck()
{
    string shapes[] = {"Heart", "Diamond", "Club", "Spade"};
    for (int i = 1; i <= 13; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            card newCard(i, shapes[j]);
            Deck.push_back(newCard);
        }
    }
}


void Game::shuffleDeck()
{
    srand(time(NULL)); // Initialize random seed
    random_shuffle(Deck.begin(), Deck.end()); // Shuffle the deck
}

void Game::dealingCards()
{
    for (int i = 1; i <= 26; i++)
    {
        player1.setCardPlay(Deck.back());
        Deck.pop_back();
        player2.setCardPlay(Deck.back());
        Deck.pop_back();
    }
    
}

void Game::playTurn() {
    countTurn++;
    turnstatics = " Turn " + std::to_string(countTurn) + ":";

    if (player1.getName() == player2.getName()) {
        throw std::logic_error("Both players have the same name!");
    }

    if (player1.stacksize() == 0 || player2.stacksize() == 0) {
        throw std::runtime_error("ERROR: A player's deck is empty, cannot play turn.");
    }

    if (player1.getDeckPlay().empty() || player2.getDeckPlay().empty()) {
        // A player's deck is empty, game over
        if (player1.getDeckPlay().empty()) {
            player2.incrementWinCount();
            player1.incrementLoseCount();
            turnstatics += " " + player2.getName() + " wins the game!";
        } else if (player2.getDeckPlay().empty()) {
            player1.incrementWinCount();
            player2.incrementLoseCount();
            turnstatics += " " + player1.getName() + " wins the game!";
        }
        else{
            player1.incrementDrawCount();
            player2.incrementDrawCount();
        }
        return;
    }

    card card1 = player1.getCardPlay();
    card card2 = player2.getCardPlay();
    turnstatics += " " + player1.getName() + " played " + std::to_string(card1.getNumber()) +  ", " + player2.getName() + " played " + std::to_string(card2.getNumber()) + ".";



    if (card1.getNumber() > card2.getNumber()) {
        
        if(card1.getNumber() == 13 && card2.getNumber() == 2) // ace loses to 2
    {
        player2.setCardEarn(card1);
        player2.setCardEarn(card2);
        player2.incrementWinCount();
        player1.incrementLoseCount();
        return;
    }
        // player 1 wins
        turnstatics += " " + player1.getName() + " wins the turn!";
        player1.setCardEarn(card1);
        player1.setCardEarn(card2);
        player1.incrementWinCount();
        player2.incrementLoseCount();
    } else if (card2.getNumber() > card1.getNumber()) {
        if(card1.getNumber() == 2 && card2.getNumber() == 13)//ace loses to 2
    {
        player1.setCardEarn(card1);
        player1.setCardEarn(card2);
        player1.incrementWinCount();
        player2.incrementLoseCount();
        return;
    }
        // player 2 wins
        turnstatics += " " + player2.getName() + " wins the turn!";
        player2.setCardEarn(card2);
        player2.setCardEarn(card1);
        player2.incrementWinCount();
        player1.incrementLoseCount();
    } else if (card1.getNumber() == card2.getNumber() && !player1.getDeckPlay().empty() && !player2.getDeckPlay().empty()) {
    // tie breaker handling
    player1.incrementDrawCount();
    player2.incrementDrawCount();
    std::vector<card> cards;
    cards.push_back(card1);
    cards.push_back(card2);

    for (int i = 0; i < 3; i++) {
        // draw three more cards
        if (player1.getDeckPlay().empty() || player2.getDeckPlay().empty()) {
            break;
        }
        card card3 = player1.getCardPlay();
        card card4 = player2.getCardPlay();
        cards.push_back(card3);
        cards.push_back(card4);

        if (card3.getNumber() > card4.getNumber()) {
            // player 1 wins
            turnstatics += " " + player1.getName() + " wins the turn!";
            for (const auto& c : cards) {
                player1.setCardEarn(c);
            }
            player1.incrementWinCount();
            player2.incrementLoseCount();
            return;
        } else if (card4.getNumber() > card3.getNumber()) {
            // player 2 wins
            turnstatics += " " + player2.getName() + " wins the turn!";
            for (const auto& c : cards) {
                player2.setCardEarn(c);
            }
            player2.incrementWinCount();
            player1.incrementLoseCount();
            return;
            }
        }
    }
}

void Game:: playAll(){
    while(player1.deckPlayNOTempty() || player2.deckPlayNOTempty()){
        playTurn();
    }
    
}

void Game::printWiner(){
    if(player1.getWinCount() > player2.getWinCount()){
        cout << player1.getName() << " is the winner!" << endl;
    }
    else if(player2.getWinCount() > player1.getWinCount()){
        cout << player2.getName() << " is the winner!" << endl;
    }
    else{
        cout << "It's a draw!" << endl;
    }
}

void Game::printLog(){
    cout << "----- GAME LOG -----" << endl;
    for (size_t i = 0; i < gamestatics.size(); i++) {
        cout << gamestatics[i] << endl;
    }
}

void Game::printStats(){
    player1.calculateStatistics(Deck);
    player2.calculateStatistics(Deck);
    cout << "Total Statistics:" << endl;
    cout << player1.getName() << " - Wins: " << player1.getWinCount() << ", Losses: " << player1.getLoseCount() << ", Draws: " << player1.getDrawCount() << endl;
    cout << player2.getName() << " - Wins: " << player2.getWinCount() << ", Losses: " << player2.getLoseCount() << ", Draws: " << player2.getDrawCount() << endl;
}

void Game::printLastTurn(){
    if(gamestatics.empty()){
        cout << "No turns have been recorded yet" << endl;
    }
    else if(player1.cardesTaken() == 0 && player2.cardesTaken() == 0){
        cout << "No turns have been played yet" << endl;
    }
    else{
        cout <<"\n"<< gamestatics.back() << endl;
    }     
}



