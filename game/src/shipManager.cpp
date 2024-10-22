#include "shipManager.h"
#include "errors/indexOutOfBounds.h"
#include "errors/invalidShipPosition.h"

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
    if(index >= ships.size() || index < 0){
        throw indexOutOfBounds(index, ships.size()-1);
    }
    return ships[index];
}
int shipManager::getLen() const{
    return ships.size();
}

void shipManager::closeShips(int length, std::pair<int, int>coordinates, bool is_vertical){
    int len_subtr_y = is_vertical ? length-1 : 0;
    int len_subtr_x = is_vertical ? 0 : length-1;
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
            throw invalidShipPosition(Ship(length, coordinates, is_vertical), ship);
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
                throw invalidShipPosition(Ship(length, coordinates, is_vertical), ship);
            }
        }
    }    
}

void shipManager::addShip(Ship ship){
    closeShips(ship.getLen(), ship.getCoor(), ship.IsVertical());
    return ships.push_back(ship);
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

segmentState shipManager::getSegmentOrAttack(std::pair <int, int> coordinates, bool to_attack){
    for(Ship &ship: ships){
        if(ship.IsVertical()){
            
            if(coordinates.first == ship.getCoor().first && 
            ship.getCoor().second <= coordinates.second && coordinates.second <= ship.getCoor().second+ship.getLen()-1){
                int index = coordinates.second - ship.getCoor().second;
                if(to_attack){
                    ship.Attack(index);
                }
                return ship.getSegment(index);
            }
        }
        else{
            if(coordinates.second == ship.getCoor().second && 
            ship.getCoor().first <= coordinates.first && coordinates.first <= ship.getCoor().first+ship.getLen()-1){
                int index = coordinates.first - ship.getCoor().first;
                if(to_attack){
                    ship.Attack(index);
                }
                return ship.getSegment(index);
            }
        }
    }
    return null;
}


