#ifndef CARD_HPP_
#define CARD_HPP_

#include <string>

namespace ariel {

    class card {
        private:
            int number;
            std::string shape;
        public:
            card(int _number, std::string _shape);
            
            void printCard();
            int getNumber() ;
            std::string getShape();
    };
}

#endif
