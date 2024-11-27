#ifndef SEABATTLE_SHIP_H
#define SEABATTLE_SHIP_H

#include <memory>
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
                Segment(segmentState state): state(state){}
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
        Ship(const json & data);

        Ship& operator = (const Ship& ship);
        Ship & operator = (Ship && ship);
        int getLen() const;
        box2d getArea() const;
        bool IsVertical() const;
        std::vector<std::shared_ptr<Segment>> & getSegments();
        bool isDestroyed();
        friend class inputManager;
        
        json toJson();
};

#endif