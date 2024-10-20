#pragma once
#include "Ship.h"

class shipManager{
    std::vector<Ship> ships;
    public:
        shipManager() = default;
        shipManager(std::initializer_list<int> lengths, 
                    std::initializer_list<std::pair<int, int>> coordinates_arr, 
                    std::initializer_list<bool> is_vertical_arr);
        shipManager(const shipManager &ship_manager);
        shipManager& operator = (const shipManager& ship_manager);
        shipManager(shipManager && ship_manager) noexcept;
        shipManager& operator = (shipManager && ship_manager) noexcept;

        Ship getShip(int index) const;
        int getLen() const;

        bool closeShips(int length, std::pair<int, int>coordinates, bool is_vertical);
        void addShip(int length, std::pair<int, int>coordinates, bool is_vertical);
        bool checkPoint(std::pair<int, int> coordinates);
        bool Attack(std::pair<int, int> coordinates);
        
        
};