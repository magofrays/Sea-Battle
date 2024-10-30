#include "Ship.h"

void Ship::Segment::Attack(){
    switch(state){
        case Ship::Segment::normal:
            state = Ship::Segment::damaged;
            break;
        case Ship::Segment::damaged:
            state = Ship::Segment::destroyed;
    }
}

Ship::Ship(int length, point2d coordinates, bool is_vertical)
: length(length), is_vertical(is_vertical){
    if(length < 1 || length > 4 ){
        throw invalidShipLength(length);
    }
    box2d area;
    area.min_point = coordinates;
    
    if(is_vertical){
        area.max_point = point2d(coordinates.x, coordinates.y+length-1);
        
    }
    else{
        area.max_point = point2d(coordinates.x+length-1, coordinates.y);
    }
    this->area = area;
    for(int i = 0; i != length; i++){
        segments.push_back(std::make_shared<Segment>());
    }
} 
Ship::Ship(const Ship &ship) : length(ship.length), area(area),
         is_vertical(ship.is_vertical), segments(ship.segments){
         } 

Ship& Ship::operator = (const Ship & ship){ 
    if(this != &ship){
        is_vertical = ship.is_vertical;
        length = ship.length;
        area = ship.area;
        segments = ship.segments;
    }
    return *this;
}

Ship & Ship::operator = (Ship && ship){
    if(this != &ship){
        is_vertical = std::move(ship.is_vertical);
        length = std::move(ship.length);
        area = std::move(ship.area);
        segments.clear();
        for(auto & segment: ship.segments){
            segments.push_back(segment);
        }
        ship.segments.clear();
    }
    return *this;
}

int Ship::getLen() const{
    return length;
}
box2d Ship::getArea() const{
    return area;
}
bool Ship::IsVertical() const{
    return is_vertical;
}
std::vector<std::shared_ptr<Ship::Segment>> & Ship::getSegments(){
    return segments;
}

bool Ship::isDestroyed(){
    bool is_destroyed = true;
    for(std::shared_ptr<Segment> & segment: segments){
        if(segment->state != Segment::destroyed){
            is_destroyed = false;
            break;
        }
    }
    return is_destroyed;
}

