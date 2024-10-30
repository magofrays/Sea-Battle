#pragma once
#include "shipManager.h"
#include "errors/objectOutOfBounds.h"

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
            void Attack(bool change_state);
    };

    private:
        box2d area;
        std::vector<std::vector<Cell>> field;   
    public:
        playField() = default;
        playField(int size_x, int size_y);
        playField(point2d size);
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field) noexcept;
        playField& operator = (playField && play_field) noexcept;
        
        void placeShip(std::shared_ptr<Ship> ship, shipManager & ship_manager);
        
        box2d getArea() const;
        Cell getCell(int x, int y);
        void Attack(point2d coordinates, bool sneak);
};

class invalidFieldSize: public std::exception{
    std::string msg;
    public:
        invalidFieldSize(){
            msg = "Field size is below 1!\n";
        }
        const char * what()  const noexcept override{
            return msg.c_str();
        }
};