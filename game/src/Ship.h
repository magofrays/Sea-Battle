#include <bits/stdc++.h>

class Ship{
    enum segmentState{
        normal,
        damaged,
        destroyed
    };
    std::vector<segmentState> segments;
    bool is_vertical = true;
    std::pair<int, int> coordinates;
    int length;
    public:
        Ship() = default;
        Ship(int length, std::pair<int, int> coordinates, bool is_vertical);
        Ship(const Ship &ship);
        Ship& operator = (const Ship& ship);
        Ship(Ship && ship) noexcept;
        Ship& operator = (Ship && ship) noexcept;
        friend std::istream& operator >> (std::istream& in, Ship& ship);
        friend std::ostream& operator << (std::ostream& out, Ship& ship);

        int getLen() const;
        std::pair<int, int> getCoor() const;
        bool IsVertical() const;
        segmentState getSegment(int index) const;

        void Attack(int index);
        bool isDestroyed();
};