#include "Ship.h"


Ship::Ship(): coordinates({0, 0}), length(0), is_vertical(true){};
Ship::Ship(size_t length, std::pair<size_t, size_t> coordinates, bool is_vertical)
: length(length), coordinates(coordinates), is_vertical(is_vertical), segments(length, normal){} 
Ship::Ship(const Ship &ship) : length(ship.length), coordinates(ship.coordinates), segments(ship.segments){} // copy construct
Ship& Ship::operator = (const Ship& ship){ 
    if(this != &ship){
        length = ship.length;
        coordinates = ship.coordinates;
        segments = ship.segments;
    }
    return *this;
}
Ship::Ship(Ship && ship) : length(std::move(ship.length)), is_vertical(std::move(ship.is_vertical)){
    coordinates = std::move(ship.coordinates);
    segments = std::move(ship.segments);
}
Ship& Ship::operator = (Ship && ship){
    if(this != &ship){
        length = std::move(ship.length);
        is_vertical = std::move(ship.is_vertical);
        coordinates = std::move(ship.coordinates);
        segments = std::move(ship.segments);
        }
    return *this;
}

size_t Ship::getLen() const{
    return length;
}

std::pair<size_t, size_t> const Ship::getCoor(){
    return coordinates;
}

bool Ship::IsVertical(){
    return is_vertical;
}

void Ship::Attack(size_t index){
    switch(segments[index]){
        case normal:
            segments[index] = damaged;
            break;
        case damaged:
            segments[index] = destroyed;
            break;
        default:
            break;
    }
}

Ship::segmentState Ship::getSegment(size_t index) const{
    return segments[index];
}

bool Ship::isDestroyed(){
    bool isDestroyed = true;
    for(segmentState segment: segments){
        if(segment != destroyed){
            isDestroyed = false;
            break;
        }
    }
    return isDestroyed;
}
