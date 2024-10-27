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
        Ship(int length, std::pair<int, int> coordinates, bool is_vertical);
        Ship(const Ship &ship);
        Ship& operator = (const Ship& ship);

        int getLen() const;
        box2d getArea() const;
        bool IsVertical() const;
        std::vector<std::shared_ptr<Segment>> & getSegments();

        //void Attack(int index);
        bool isDestroyed();
};