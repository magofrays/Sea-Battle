#pragma once
#include "playField.h"
class inputManager{
    std::istream & is;
    public:
        inputManager(std::istream & is);
        void inputCoordinates(point2d & coordinates);
        void inputShip(std::shared_ptr<Ship> ship);
        void inputAction(char & c);
};

class inputException : public std::exception {
        std::string msg;  
            public:
                inputException() {
                    msg = "Your input is wrong somewhere!\n";
                }

                const char* what() const noexcept override {
                    return msg.c_str(); 
                }
};