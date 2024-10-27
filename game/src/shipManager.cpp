#include "shipManager.h"
//#include "errors/indexOutOfBounds.h"
//#include "errors/invalidShipPosition.h"

shipManager::shipManager(const shipManager &ship_manager):ships(ship_manager.ships){}
shipManager& shipManager::operator = (const shipManager& ship_manager){
    if(this != &ship_manager){
        ships = ship_manager.ships;
    }
    return *this;
}

int shipManager::getLen() const{
    return ships.size();
}

bool shipManager::shipIntersection(box2d ship_area){
    for(const std::shared_ptr<Ship> & otherShip: ships){
        box2d area_around_other_ship = (*otherShip).getArea();
        area_around_other_ship.min_point -= point2d(1, 1);
        area_around_other_ship.max_point += point2d(1, 1);

        if(area_around_other_ship.intersects(ship_area)){
            return true;
        }
    }
    return false;
}

void shipManager::addShip(std::shared_ptr<Ship> & ship){
    ships.push_back(ship);
}
