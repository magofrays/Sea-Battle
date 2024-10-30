#pragma once
#include "utilities/vector2d.h"

class Ship{
    public:
        class Segment{
            public:
                enum segmentState{
                    normal,
                    damaged,
                    destroyed,
                };
                segmentState state;
                Segment():state(normal){}
                void Attack();
        };

    private:
        std::vector<std::shared_ptr<Segment>> segments;
        bool is_vertical = true;
        box2d area;
        int length;
    public:
        Ship() = default;
        Ship(int length, point2d coordinates, bool is_vertical);
        Ship(const Ship &ship);
        Ship& operator = (const Ship& ship);
        Ship & operator = (Ship && ship);
        int getLen() const;
        box2d getArea() const;
        bool IsVertical() const;
        std::vector<std::shared_ptr<Segment>> & getSegments();
        bool isDestroyed();
        friend class inputManager;
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