#pragma once
#include "shipManager.h"

class playField{
    public:
        class Cell{
        public:
            enum cellState{
                unknown,
                empty,
                ship
            };
            std::shared_ptr<Ship::Segment> segment;
            cellState state;
            Cell():segment(nullptr), state(unknown){}
            void Attack();
    };

    private:
        box2d area;
        std::vector<std::vector<Cell>> field;   
    public:
        playField() = default;
        playField(int size_x, int size_y);
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field) noexcept;
        playField& operator = (playField && play_field) noexcept;
        
        void placeShip(std::shared_ptr<Ship> ship, shipManager & ship_manager);
        
        box2d getArea() const;
        Cell & getCell(int x, int y);
        void Attack(int x, int y);
};