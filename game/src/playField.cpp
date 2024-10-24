#include "playField.h"
#include "errors/objectOutOfBounds.h"

playField::playField(int size_x, int size_y) :
        size_x(size_x), size_y(size_y) {
            field.resize(size_y, std::vector<cell>(size_x, unknown));
        }

playField::playField(const playField &play_field):size_x(play_field.size_x), 
    size_y(play_field.size_y), field(play_field.field){
    }

playField& playField::operator = (const playField& play_field){
    if(this != &play_field){
        size_x = play_field.size_x;
        size_y = play_field.size_y;
        field = play_field.field;
    }
    return *this;
}
playField::playField(playField && play_field) noexcept :size_x(std::move(play_field.size_x)), 
                                              size_y(std::move(play_field.size_y))
                                            {
    field = std::move(play_field.field);
    play_field.field.clear();
}
playField& playField::operator = (playField && play_field) noexcept {
    if(this != &play_field){
        size_x = std::move(play_field.size_x);
        size_y = std::move(play_field.size_y);
        field = std::move(play_field.field);
    }
    return *this;
}

bool playField::inField(int length, std::pair<int, int>coordinates, bool is_vertical){
    int len_subtr_y = is_vertical ? length-1 : 0;
    int len_subtr_x = is_vertical ? 0 : length-1;
    if(0 <= coordinates.first && coordinates.first + len_subtr_x <= size_x-1 && 
        0 <= coordinates.second && coordinates.second + len_subtr_y <= size_y-1 
    ){
        return true;
        }
    return false;
}

void playField::addShip(Ship ship, shipManager & ship_manager){
    if(inField(ship.getLen(), ship.getCoor(), ship.IsVertical())){
        return ship_manager.addShip(ship);
    }
    throw objectOutOfBounds(ship.getCoor());
}


segmentState playField::getSegmentOrAttack(std::pair<int, int> coordinates, bool to_attack,  shipManager & ship_manager){
    if(inField(1, coordinates, true)){
        segmentState segment = ship_manager.getSegmentOrAttack(coordinates, to_attack);
        if(to_attack){
            if(segment != null){
                field[coordinates.second][coordinates.first] = ship;
            }
            else{
                field[coordinates.second][coordinates.first] = empty;
            }
        }
        return segment;
        
    }
    throw objectOutOfBounds(coordinates);
}

std::pair<int, int> playField::getSize(){
    std::pair<int, int> size = {size_x, size_y};
    return size;
}
