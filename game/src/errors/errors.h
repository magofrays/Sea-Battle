#pragma once
#include "../utilities/vector2d.h"
class objectOutOfBounds : public std::exception {
    point2d coordinates;
    std::string msg;
    public:
        objectOutOfBounds(point2d coordinates) : coordinates(coordinates) {
            msg = "Object located at (" + std::to_string(coordinates.x) +
                ", " + std::to_string(coordinates.y) + ") is out of bounds!\n";
        }

        const char * what() const noexcept override {
            return msg.c_str();
        }
};

class invalidFieldSize: public std::exception{
    std::string msg;
    public:
        invalidFieldSize(){
            msg = "Field size is below 1!\n";
        }
        const char * what()  const noexcept override{
            return msg.c_str();
        }
};

class invalidShipLength : public std::exception {
    int length;
    std::string msg;  

    public:
        invalidShipLength(int length) : length(length) {
            msg = "Ship length is " + std::to_string(length) + ", but must be between 1 and 4\n";
        }

        const char* what() const noexcept override {
            return msg.c_str(); 
        }
};

class invalidShipPosition: public std::exception{
    std::string msg;
    public:
        invalidShipPosition(){
                msg = "Ship intersects other ship\n";
            }
        const char* what() const noexcept override {
            return msg.c_str();
        }
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