#include "playField.h"
void playField::Cell::Attack(bool change_state){
    if(!segment){
        if(change_state){
            state = playField::Cell::empty;
        }
    }
    else{
        if(change_state){
            state = playField::Cell::ship;
        }
        segment->Attack();
    }
}

playField::playField(int size_x, int size_y)
{
    if(size_x < 1 || size_y < 1){
        throw invalidFieldSize();
    }
    box2d area(point2d(0, 0), point2d(size_x, size_y));
    this->area = area;
    field.resize(size_y, std::vector<Cell>(size_x));
}

playField::playField(point2d size){
    if(size.x < 1 || size.y < 1){
        throw invalidFieldSize();
    }
    box2d area(point2d(0, 0), size);
    this->area = area;
    field.resize(size.y, std::vector<Cell>(size.x));
}

playField::playField(const playField &play_field):area(play_field.area), field(play_field.field){
    }

playField& playField::operator = (const playField& play_field){
    if(this != &play_field){
        area = play_field.area;
        field = play_field.field;
    }
    return *this;
}
playField::playField(playField && play_field) noexcept :area(std::move(play_field.area))
                                            {
    field = std::move(play_field.field);
    play_field.field.clear();
}
playField& playField::operator = (playField && play_field) noexcept {
    if(this != &play_field){
        area = std::move(play_field.area);
        field = std::move(play_field.field);
    }
    return *this;
}

void playField::placeShip(std::shared_ptr<Ship> ship, shipManager & ship_manager){
    box2d ship_area = ship->getArea();
    if( area.contains(ship_area) && !(ship_manager.shipIntersection( ship_area )) ){
        ship_manager.addShip(ship);
        auto segments = ship->getSegments();
        if(ship->IsVertical()){
            
            int x = ship_area.min_point.x; int y_min = ship_area.min_point.y;
            
            for(int y = y_min; y != ship_area.max_point.y+1; y++){
                field[y][x].segment = segments[y-y_min];
            }
        }
        else{
            int y = ship_area.min_point.y; int x_min = ship_area.min_point.x;
            for(int x = x_min; x != ship_area.max_point.x+1; x++){
                field[y][x].segment = segments[x-x_min];
            }
        }
    }
    else{
        if(!area.contains(ship->getArea()))
            throw objectOutOfBounds(ship->getArea().min_point);
        throw invalidShipPosition();
    }
}

box2d playField::getArea() const{
    return area;
}

playField::Cell playField::getCell(int x, int y){
    return field[y][x];
}

void playField::Attack(point2d coordinates, bool sneak){
    if(!(area.contains(coordinates))){
        throw objectOutOfBounds(coordinates);
    }
    (field[coordinates.y][coordinates.x]).Attack(sneak);
};
