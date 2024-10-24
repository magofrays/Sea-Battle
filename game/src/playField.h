#pragma once
#include "shipManager.h"

class playField{
    public:
        enum cell{
            unknown,
            empty,
            ship
        };
    private:
        int size_x;
        int size_y;
        
        std::vector<std::vector<cell>> field;   
    public:
        playField() = default;
        playField(int size_x, int size_y);
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field) noexcept;
        playField& operator = (playField && play_field) noexcept;
        
        bool inField(int length, std::pair<int, int>coordinates, bool is_vertical);
        void addShip(Ship ship, shipManager & ship_manager);
        segmentState getSegmentOrAttack(std::pair<int, int> coordinates, bool to_attack, shipManager & ship_manager);
        
        std::pair<int, int> getSize();
};