#pragma once
#include "shipManager.h"

class playField{
    enum cell{
        unknown,
        empty,
        ship
    };
    int size_x;
    int size_y;
    shipManager & ship_manager;
    std::vector<std::vector<cell>> field;
    public:
        playField() = default;
        playField(int size_x, int size_y, shipManager & ship_manager);
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field) noexcept;
        playField& operator = (playField && play_field) noexcept;

        shipManager & getShipManager() const;
        
        bool inField(int length, std::pair<int, int>coordinates, bool is_vertical);
        void addShip(int length, std::pair<int, int>coordinates, bool is_vertical);
        void Attack(std::pair<int, int> coordinates);
        
        std::pair<int, int> getSize();
        
        void printField();
};