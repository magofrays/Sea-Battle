#pragma once
#include "Ship.h"

class shipManager{
    std::vector<std::shared_ptr<Ship>> ships;
    int destroyed_ships;
    public:
        shipManager() = default;
        shipManager(const shipManager &ship_manager);
        shipManager& operator = (const shipManager& ship_manager);
        
        int getLen() const;

        bool shipIntersection(box2d ship_area);
        void addShip(std::shared_ptr<Ship> ship);
        bool checkDestroyedShips();
        bool allShipsDestroyed();
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