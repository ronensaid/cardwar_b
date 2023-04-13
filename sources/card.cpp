#include<iostream>
#include "card.hpp"

using namespace std;

namespace ariel {
    card::card(int _number ,string _shape)
    {
        this->shape = _shape;
        switch(number) {
        case 1:
            this->number = 13; // Ace
            break;
        case 11:
            this->number = 10; // Jack
            break;
        case 12:
            this->number = 11; // Queen
            break;
        case 13:
            this->number = 12; // King
            break;
        default:
            this->number = _number;
            break;
    }
    }
    
    void card::printCard()
    {
        cout << number << " is " << shape;
    }

    int card::getNumber()
    {
        return number;
    }

    string card::getShape()
    {
        return shape;
    }
}
