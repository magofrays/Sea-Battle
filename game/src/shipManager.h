#pragma once
#include "Ship.h"

class shipManager{
    std::vector<Ship> ships;
    public:
        shipManager() = default;
        shipManager(const shipManager &ship_manager);
        shipManager& operator = (const shipManager& ship_manager);
        shipManager(shipManager && ship_manager) noexcept;
        shipManager& operator = (shipManager && ship_manager) noexcept;
        
        Ship getShip(int index) const;
        int getLen() const;

        void closeShips(int length, std::pair<int, int>coordinates, bool is_vertical);
        void addShip(Ship ship);
        bool checkPoint(std::pair<int, int> coordinates);
        segmentState getSegmentOrAttack(std::pair<int, int> coordinates, bool to_attack);
        
        
};