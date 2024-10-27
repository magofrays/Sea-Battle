#include "playField.h"
#include "errors/objectOutOfBounds.h"
#include "errors/invalidShipPosition.h"


void playField::Cell::Attack(){
    if(!segment){
        state = playField::Cell::empty;
    }
    else{
        state = playField::Cell::ship;
        (*segment).Attack();
    }
}

playField::playField(int size_x, int size_y)
        {
            box2d area(point2d(0, 0), point2d(size_x, size_y));
            this->area = area;
            field.resize(size_y, std::vector<Cell>(size_x)) ;
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
    box2d ship_area = (*ship).getArea();
    if( area.contains(ship_area) && !(ship_manager.shipIntersection( ship_area )) ){
        ship_manager.addShip(ship);
        auto segments = (*ship).getSegments();
        if((*ship).IsVertical()){
            
            int x = ship_area.min_point.x; int y_min = ship_area.min_point.y;
            
            for(int y = y_min; y != ship_area.max_point.y; y++){
                field[y][x].segment = segments[y-y_min];
            }
        }
        else{
            int y = ship_area.min_point.y; int x_min = ship_area.min_point.x;
            for(int x = x_min; x != ship_area.max_point.x; x++){
                field[y][x].segment = segments[x-x_min];
            }
        }
    }
    else{
        throw invalidShipPosition();
    }
}

box2d playField::getArea() const{
    return area;
}

playField::Cell & playField::getCell(int x, int y){
    return field[y][x];
}

void playField::Attack(int x, int y){
    if(!(area.contains(point2d(x, y)))){
        throw objectOutOfBounds({x, y});
    }
    (field[y][x]).Attack();
};
