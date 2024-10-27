#pragma once
#include "Ship.h"

class shipManager{
    std::vector<std::shared_ptr<Ship>> ships;
    public:
        shipManager() = default;
        shipManager(const shipManager &ship_manager);
        shipManager& operator = (const shipManager& ship_manager);
        
        int getLen() const;

        bool shipIntersection(box2d ship_area);
        void addShip(std::shared_ptr<Ship> & ship);   
};