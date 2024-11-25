#include "playField.h"
#include "errors/errors.h"
#include "shipManager.h"
#include "utilities/settings.h"

void playField::Cell::Attack(bool sneak){
    if(!segment){
        if(!sneak){
            state = playField::Cell::empty;
        }
    }
    else{
        if(!sneak){
            state = playField::Cell::ship;
        }
        segment->Attack();
    }
}

playField::playField(int size_x, int size_y)
{
    if(size_x < 1 || size_y < 1 || size_x > seabattle::MAX_FIELD_SIZE || size_y > seabattle::MAX_FIELD_SIZE){
        throw invalidFieldSize(size_x, size_y);
    }
    box2d area(point2d(0, 0), point2d(size_x-1, size_y-1));
    this->area = area;
    field.resize(size_y, std::vector<Cell>(size_x));
}

playField::playField(point2d size){
    if(size.x < 1 || size.y < 1){
        throw invalidFieldSize(size.x, size.y);
    }
    box2d area(point2d(0, 0), size);
    this->area = area;
    field.resize(size.y+1, std::vector<Cell>(size.x+1));
}

playField::playField(const json & data){ // we trust json
    int size_x = data["width"];
    int size_y = data["height"];
    field.resize(size_y, std::vector<Cell>(size_x));
    for(int y = 0; y != size_y; y++){
        for(int x = 0; x != size_x; x++){
            field[y][x].state = data["playField"][y][x];
        }
    }
}

playField::playField(const playField &play_field):area(play_field.area), field(play_field.field){}

playField& playField::operator = (const playField& play_field){
    if(this != &play_field){
        area = play_field.area;
        field = play_field.field;
    }
    return *this;
}
playField::playField(playField && play_field) :area(std::move(play_field.area))
                                            {
    field = std::move(play_field.field);
    play_field.field.clear();
}
playField& playField::operator = (playField && play_field) {
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
    if(!(area.contains(box2d(coordinates, coordinates)))){
        throw objectOutOfBounds(coordinates);
    }
    (field[coordinates.y][coordinates.x]).Attack(sneak);
};


json playField::toJson(){
    json data;
    data["width"] = area.max_point.x;
    data["height"] = area.max_point.y;
    for(int y = 0; y != area.max_point.y; y++){
        std::vector<int> row;
        for(int x = 0; x != area.max_point.x; x++){
            row.push_back(static_cast<int>(field[y][x].state));
        }
        data["playField"].push_back(row);
    }
    return data;
}
