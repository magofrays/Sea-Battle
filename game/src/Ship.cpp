#include "Ship.h"
#include "errors/invalidShipLength.h"
#include "errors/inputException.h"

Ship::Ship(int length, std::pair<int, int> coordinates, bool is_vertical)
: length(length), coordinates(coordinates), is_vertical(is_vertical), segments(length, normal){
    if(length < 1 || length > 4 ){
        throw invalidShipLength(length);
    }
} 
Ship::Ship(const Ship &ship) : length(ship.length), coordinates(ship.coordinates), 
                               segments(ship.segments), is_vertical(ship.is_vertical){} 

Ship& Ship::operator = (const Ship& ship){ 
    if(this != &ship){
        is_vertical = ship.is_vertical;
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

std::istream& operator>>(std::istream& in, Ship& ship) {
    std::cout << "Input format: coordinates (x y), ship length, orientation (0 horizontal, 1 vertical).\n";
    std::string input;
    std::getline(in, input);
    std::stringstream ss(input);
    int orientation = 0, x = 0, y = 0, length = 0;
    
    if (!(ss >> x >> y >> length >> orientation) || !ss.eof()){
        throw inputException();
    }
    if(length < 1 || length > 4 ){
        throw invalidShipLength(length);
    }
    bool is_vertical = (orientation == 1); 
    if (!is_vertical && orientation != 0) {
        throw inputException(); 
    }

    ship = Ship(length, {x, y}, is_vertical); 
    
    return in;
}

std::ostream& operator << (std::ostream& out, Ship& ship){
    std::string output = "Ship " + std::to_string(ship.getLen()) + " segments long, located " 
            + (ship.IsVertical() ? "vertically":"horizontally") + " at (" + std::to_string(ship.getCoor().first) + ", "
            + std::to_string(ship.getCoor().second) + ")\n";
    out << output;
    return out;
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
segmentState Ship::getSegment(int index) const{
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

