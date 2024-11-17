#include "shipManager.h"

shipManager::shipManager(const shipManager &ship_manager):ships(ship_manager.ships), destroyed_ships(ship_manager.destroyed_ships){}
shipManager::shipManager(const json & data){
    int size = data["size"];
    destroyed_ships = data["destroyed_ships"];
    for(int i = 0; i != size; i++){
        ships.push_back(std::make_shared<Ship>(data["ships"][i]));
    }
}

shipManager& shipManager::operator = (const shipManager& ship_manager){
    if(this != &ship_manager){
        ships = ship_manager.ships;
        destroyed_ships = ship_manager.destroyed_ships;
    }
    return *this;
}

int shipManager::getLen() const{
    return ships.size();
}

bool shipManager::shipIntersection(box2d ship_area){
    for(auto & ship: ships){
        
        box2d area = ship->getArea();
        area.min_point -= point2d(1, 1);
        area.max_point += point2d(1, 1);
        if(area.intersects(ship_area)){
            return true;
        }
    }
    return false;
}

void shipManager::addShip(std::shared_ptr<Ship> ship){
    ships.push_back(ship);
}

bool shipManager::checkDestroyedShips(){
    int count = 0;
    for(auto ship: ships){
        if(ship->isDestroyed()){
            count++;
        }
    }
    if(count > destroyed_ships){
        destroyed_ships = count;
        return true;
    }
    return false;
}

bool shipManager::allShipsDestroyed(){
    if(ships.size() == destroyed_ships){ 
        return true;
    }
    return false;
}

json shipManager::toJson(){
    json data;
    data["size"] = ships.size();
    data["destroyed_ships"] = destroyed_ships;
    for(int i = 0; i != ships.size(); i++){
        data["ships"].push_back(ships[i]->toJson());
    }
    return data;
}