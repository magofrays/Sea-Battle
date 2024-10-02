#include <vector>
#include <iostream>
#include <utility>
#include <initializer_list>
#include <list>
#include <cmath>

class Ship{
    enum segmentState{
        normal,
        damaged,
        destroyed
    };
    std::vector<segmentState> segments;
    bool is_vertical = true;
    std::pair<size_t, size_t> coordinates;
    size_t length;
    public:
        Ship();
        Ship(size_t length, std::pair<size_t, size_t> coordinates, bool is_vertical);
        Ship(const Ship &ship);
        Ship& operator = (const Ship& ship);
        Ship(Ship && ship);
        Ship& operator = (Ship && ship);

        size_t getLen() const;
        std::pair<size_t, size_t> getCoor() const;
        bool IsVertical() const;
        segmentState getSegment(size_t index) const;
        
        void Attack(size_t index);
        bool isDestroyed();
};