#pragma once
#include "scannerAbility.h"
#include "doubleDamageAbility.h"
#include "shellingAbility.h"

class Player;
class abilitiesManager{
    std::queue <std::shared_ptr<IAbility>> abilities;
    public:
        abilitiesManager();
        void createRandomAbility();
        void applyAbility(Player * player);
};

class noAbilitiesException : public std::exception {
        std::string msg;  
            public:
                noAbilitiesException() {
                    msg = "There are no abilities in a queue!\n";
                }

                const char* what() const noexcept override {
                    return msg.c_str(); 
                }
};