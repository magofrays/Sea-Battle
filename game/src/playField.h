#ifndef SEABATTLE_PLAYFIELD_H
#define SEABATTLE_PLAYFIELD_H

#include "utilities/vector2d.h"
#include "Ship.h"

class shipManager;

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
        playField(const json & data);
    
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field);
        playField& operator = (playField && play_field);
        
        void placeShip(std::shared_ptr<Ship> ship, shipManager & ship_manager);
        
        void loadShips(shipManager & ship_manager);

        box2d getArea() const;
        Cell getCell(int x, int y);
        void Attack(point2d coordinates, bool sneak);

        json toJson();
};

#endif