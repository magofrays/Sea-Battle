#include "Ship.h"
#include "errors/invalidShipLength.h"
#include "errors/inputException.h"


void Ship::Segment::Attack(){
    switch(state){
        case Ship::Segment::normal:
            state = Ship::Segment::damaged;
            break;
        case Ship::Segment::damaged:
            state = Ship::Segment::destroyed;
    }
}

Ship::Ship(int length, std::pair<int, int> coordinates, bool is_vertical)
: length(length), is_vertical(is_vertical){
    if(length < 1 || length > 4 ){
        throw invalidShipLength(length);
    }
    box2d area;
    area.min_point = point2d(coordinates.first, coordinates.second);
    
    if(is_vertical){
        area.max_point = point2d(coordinates.first, coordinates.second+length);
        
    }
    else{
        area.max_point = point2d(coordinates.first+length, coordinates.second);
    }
    this->area = area;
    for(int i = 0; i != length; i++){
        segments.push_back(std::make_shared<Segment>());
    }
} 
Ship::Ship(const Ship &ship) : length(ship.length), area(area),
                               segments(ship.segments), is_vertical(ship.is_vertical){} 

Ship& Ship::operator = (const Ship & ship){ 
    if(this != &ship){
        is_vertical = ship.is_vertical;
        length = ship.length;
        area = ship.area;
        segments = ship.segments;
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
        if( (*segment).state != Segment::destroyed){
            is_destroyed = false;
            break;
        }
    }
    return is_destroyed;
}

