#include "inputManager.h"

inputManager::inputManager(std::istream & is):is(is){}

void inputManager::inputCoordinates(point2d & coordinates){
    std::string input;
    std::getline(is, input);
    std::stringstream ss(input);
    int x = 0, y = 0;
    if (!(ss >> x >> y) || ss.fail() || !ss.eof()){
        throw inputException();
    }
    coordinates.x = x;
    coordinates.y = y;
}

void inputManager::inputShip(std::shared_ptr<Ship> ship){
    std::string input;
    std::getline(is, input);
    std::stringstream ss(input);
    int orientation = 0, x = 0, y = 0, length = 0;
    
    if (!(ss >> x >> y >> length >> orientation) || ss.fail() || !ss.eof()){
        throw inputException();
    }
    bool is_vertical = (orientation == 1); 
    if (!is_vertical && orientation != 0) {
        throw inputException(); 
    }
    Ship new_ship(length, {x, y}, is_vertical);
    *ship = new_ship;
}

void inputManager::inputAction(char & c){
    std::string input;
    std::getline(is, input);
    if(input != "u" && input != "a"){
        throw inputException();
    }
    c = input[0];
}