#include "inputManager.h"

std::istream& inputManager::inputShip(std::istream& in, Ship& ship){
    std::cout << "Input ship.\nFormat: coordinates (x y), ship length, orientation (0 horizontal, 1 vertical).\n";
    std::string input;
    std::getline(in, input);
    std::stringstream ss(input);
    int orientation = 0, x = 0, y = 0, length = 0;
    
    if (!(ss >> x >> y >> length >> orientation) || ss.fail() || !ss.eof()){
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

std::istream& inputManager::inputPlayField(std::istream& in, playField & play_field ){
    std::cout << "Input play field sizes. Format: x_size y_size.\n";
    std::string input;
    std::getline(in, input);
    std::stringstream ss(input);
    int x_size = 0, y_size = 0;
    
    if (!(ss >> x_size >> y_size) || ss.fail() ||!ss.eof()){
        throw inputException();
    }
    if(x_size < 1 || y_size < 1 ){
        throw invalidFieldSize();
    }

    play_field = playField(x_size, y_size); 
    
    return in;
}