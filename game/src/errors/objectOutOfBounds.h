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
