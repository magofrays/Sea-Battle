#include "playField.h"


playField::playField(int size_x, int size_y, shipManager & ship_manager) :
        size_x(size_x), size_y(size_y), ship_manager(ship_manager) {
            field.resize(size_y, std::vector<cell>(size_x, unknown));
        }

playField::playField(const playField &play_field):size_x(play_field.size_x), 
    size_y(play_field.size_y), ship_manager(play_field.ship_manager), field(play_field.field){
    }
playField& playField::operator = (const playField& play_field){
    if(this != &play_field){
        size_x = play_field.size_x;
        size_y = play_field.size_y;
        ship_manager = play_field.ship_manager;
        field = play_field.field;
    }
    return *this;
}
playField::playField(playField && play_field) noexcept :size_x(std::move(play_field.size_x)), 
                                              size_y(std::move(play_field.size_y)),
                                              ship_manager(play_field.ship_manager)
                                            {
    field = std::move(play_field.field);
    play_field.field.clear();
}
playField& playField::operator = (playField && play_field) noexcept {
    if(this != &play_field){
        size_x = std::move(play_field.size_x);
        size_y = std::move(play_field.size_y);
        ship_manager = play_field.ship_manager;
        field = std::move(play_field.field);
    }
    return *this;
}

shipManager & playField::getShipManager() const{
    return ship_manager;
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

void playField::addShip(int length, std::pair<int, int>coordinates, bool is_vertical){
    if(inField(length, coordinates, is_vertical)){
        return ship_manager.addShip(length, coordinates, is_vertical);
    }
    throw std::invalid_argument("OBJECT IS OUT OF BORDER!");
}

void playField::Attack(std::pair<int, int> coordinates){
    if(inField(1, coordinates, true)){
        if(ship_manager.Attack(coordinates)){
            field[coordinates.second][coordinates.first] = ship;
        }
        else{
            field[coordinates.second][coordinates.first] = empty;
        }
        return;
    }
    throw std::invalid_argument("COORDINATES ARE OUT OF BORDER!");
}
std::pair<int, int> playField::getSize(){
    std::pair<int, int> size = {size_x, size_y};
    return size;
}
void playField::printField(){
    for(int y = size_y-1; y != -1; y--){
        for(int x = 0; x != size_x; x++){
            char ch;
            if (field[y][x] == unknown){
                ch = '#';
            }
            else if(field[y][x] == ship){
                ch = 'x';
            }
            else{
                ch = '*';
            }
            std::cout << ch << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

