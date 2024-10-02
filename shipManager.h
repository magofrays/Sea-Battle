#include "Ship.h"

class shipManager{
    std::vector<Ship> ships;
    public:
        shipManager();
        shipManager(std::initializer_list<size_t> lengths, 
                    std::initializer_list<std::pair<size_t, size_t>> coordinates_arr, 
                    std::initializer_list<bool> is_vertical_arr);
        shipManager(const shipManager &ship_manager);
        shipManager& operator = (const shipManager& ship_manager);
        shipManager(shipManager && ship_manager);
        shipManager& operator = (shipManager && ship_manager);

        Ship getShip(size_t index) const;

        bool closeShips(size_t length, std::pair<size_t, size_t>coordinates, bool is_vertical);
        void addShip(size_t length, std::pair<size_t, size_t>coordinates, bool is_vertical);
        bool Attack(std::pair<size_t, size_t> coordinates);
        
        
};