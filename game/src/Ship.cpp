#include "Ship.h"

Ship::Ship(int length, std::pair<int, int> coordinates, bool is_vertical)
: length(length), coordinates(coordinates), is_vertical(is_vertical), segments(length, normal){
    if(length < 1 || length > 4 ){
        throw std::invalid_argument("SHIP LENGTH IS BETWEEN 1-4!");
    }
} 
Ship::Ship(const Ship &ship) : length(ship.length), coordinates(ship.coordinates), segments(ship.segments){} // copy construct
Ship& Ship::operator = (const Ship& ship){ 
    if(this != &ship){
        length = ship.length;
        coordinates = ship.coordinates;
        segments = ship.segments;
    }
    return *this;
}
Ship::Ship(Ship && ship) noexcept : length(std::move(ship.length)), is_vertical(std::move(ship.is_vertical)) {
    coordinates = std::move(ship.coordinates);
    segments = std::move(ship.segments);
}
Ship& Ship::operator = (Ship && ship) noexcept{
    if(this != &ship){
        length = std::move(ship.length);
        is_vertical = std::move(ship.is_vertical);
        coordinates = std::move(ship.coordinates);
        segments = std::move(ship.segments);
        }
    return *this;
}

int Ship::getLen() const{
    return length;
}
std::pair<int, int>  Ship::getCoor() const{
    return coordinates;
}
bool Ship::IsVertical() const{
    return is_vertical;
}
Ship::segmentState Ship::getSegment(int index) const{
    return segments[index];
}


void Ship::Attack(int index){
    switch(segments[index]){
        case normal:
            segments[index] = damaged;
            break;
        case damaged:
            segments[index] = destroyed;
            break;
    }
}

bool Ship::isDestroyed(){
    bool is_destroyed = true;
    for(segmentState segment: segments){
        if(segment != destroyed){
            is_destroyed = false;
            break;
        }
    }
    return is_destroyed;
}