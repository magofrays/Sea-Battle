#include "shipManager.h"


shipManager::shipManager(std::initializer_list<int> lengths, 
                    std::initializer_list<std::pair<int, int>> coordinates_arr, 
                    std::initializer_list<bool> is_vertical_arr){
    if(lengths.size() != coordinates_arr.size() || 
            is_vertical_arr.size() != coordinates_arr.size() ||
            lengths.size() != is_vertical_arr.size()){
        throw std::invalid_argument("ARRAYS MUST HAVE SAME SIZE!");
    }
    auto length = lengths.begin();
    auto coordinates = coordinates_arr.begin();
    auto is_vertical = is_vertical_arr.begin();

    while (length != lengths.end()) {
        this->addShip(*length, *coordinates, *is_vertical);
        ++length;
        ++coordinates;
        ++is_vertical;
    }
    };

shipManager::shipManager(const shipManager &ship_manager):ships(ship_manager.ships){}
shipManager& shipManager::operator = (const shipManager& ship_manager){
    if(this != &ship_manager){
        ships = ship_manager.ships;
    }
    return *this;
}
shipManager::shipManager(shipManager && ship_manager)noexcept:ships(std::move(ship_manager.ships)){}
shipManager& shipManager::operator = (shipManager && ship_manager)noexcept{
    if(this != &ship_manager){
        ships = std::move(ship_manager.ships);
    }
    return *this;
}

Ship shipManager::getShip(int index) const{
    if(index >= ships.size()){
        throw(std::invalid_argument("INDEX OUT OF RANGE\n"));
    }
    return ships[index];
}
int shipManager::getLen() const{
    return ships.size();
}

bool shipManager::closeShips(int length, std::pair<int, int>coordinates, bool is_vertical){
    int len_subtr_x = is_vertical ? length-1 : 0;
    int len_subtr_y = is_vertical ? 0 : length-1;
    bool close_to_ship = false;
    for(Ship & ship: ships){
        if(ship.IsVertical()){
            if(
        (ship.getCoor().first-1 <= coordinates.first && coordinates.first <= ship.getCoor().first+1
        &&
        ship.getCoor().second-1 <= coordinates.second && coordinates.second <= ship.getCoor().second+ship.getLen()) 
        ||
        (ship.getCoor().first-1 <= coordinates.first+len_subtr_x  && coordinates.first+len_subtr_x <= ship.getCoor().first+1
        &&
        ship.getCoor().second-1 <= coordinates.second+len_subtr_y && coordinates.second+len_subtr_y <= ship.getCoor().second+ship.getLen()) 
                ) 
                {
                    std::cerr << "SHIP x:" << coordinates.first << ", y:" << coordinates.second << ", length:" << length 
                    << ", positioned:" << (is_vertical ? "vertical\n" : "horizontal\n");
                    std::cerr << "CLOSE TO\nSHIP x:" << ship.getCoor().first << ", y:" << ship.getCoor().second << ", length:" << ship.getLen()
                    << ", positioned:" << (ship.IsVertical() ? "vertical\n\n" : "horizontal\n\n");
                    close_to_ship = true;
                    break;
                }
        }
        else{
            if(
        (ship.getCoor().first-1 <= coordinates.first && coordinates.first <= ship.getCoor().first+ship.getLen()
        &&
        ship.getCoor().second-1 <= coordinates.second && coordinates.second <= ship.getCoor().second+1) 
        ||
        (ship.getCoor().first-1 <= coordinates.first+len_subtr_x  && coordinates.first+len_subtr_x <= ship.getCoor().first+ship.getLen()
        &&
        ship.getCoor().second-1 <= coordinates.second+len_subtr_y && coordinates.second+len_subtr_y <= ship.getCoor().second+1) 
                )  
                {
                    std::cerr << "SHIP x:" << coordinates.first << ", y:" << coordinates.second << ", length:" << length 
                    << ", positioned:" << (is_vertical ? "vertical\n" : "horizontal\n");
                    std::cerr << "CLOSE TO\nSHIP x:" << ship.getCoor().first << ", y:" << ship.getCoor().second << ", length:" << ship.getLen()
                    << ", positioned:" << (ship.IsVertical() ? "vertical\n\n" : "horizontal\n\n");
                    close_to_ship = true;
                    break;
                }
        }
    }    
return close_to_ship;
}

void shipManager::addShip(int length, std::pair<int, int>coordinates, bool is_vertical){
    if(!closeShips(length, coordinates, is_vertical)){
        return ships.push_back(Ship(length, coordinates, is_vertical));
    }
    throw std::invalid_argument("SHIP CLOSE TO SHIP OR SHIPS!");
}

bool shipManager::checkPoint(std::pair <int, int> coordinates){
    for(Ship &ship: ships){
        if(ship.IsVertical()){
            if(coordinates.first == ship.getCoor().first && 
            ship.getCoor().second <= coordinates.second && coordinates.second <= ship.getCoor().second+ship.getLen()-1){
                return true;
            }
        }
        else{
            if(coordinates.second == ship.getCoor().second && 
            ship.getCoor().first <= coordinates.first && coordinates.first <= ship.getCoor().first+ship.getLen()-1){
                return true;
            }
        }
    }
    return false;
}

bool shipManager::Attack(std::pair <int, int> coordinates){
    for(Ship &ship: ships){
        if(ship.IsVertical()){
            
            if(coordinates.first == ship.getCoor().first && 
            ship.getCoor().second <= coordinates.second && coordinates.second <= ship.getCoor().second+ship.getLen()-1){
                int index = coordinates.second - ship.getCoor().second;
                ship.Attack(index);
                return true;
            }
        }
        else{
            if(coordinates.second == ship.getCoor().second && 
            ship.getCoor().first <= coordinates.first && coordinates.first <= ship.getCoor().first+ship.getLen()-1){
                int index = coordinates.first - ship.getCoor().first;
                ship.Attack(index);
                return true;
            }
        }
    }
    return false;
}


