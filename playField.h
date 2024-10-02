#include "shipManager.h"

class playField{
    enum cell{
        unknown,
        empty,
        ship
    };
    size_t size_x;
    size_t size_y;
    shipManager ship_manager;
    std::vector<std::vector<cell>> field;
    public:
        playField();
        playField(size_t size_x, size_t size_y);
        playField(size_t size_x, size_t size_y, 
                    std::initializer_list<size_t> lengths, 
                    std::initializer_list<std::pair<size_t, size_t>> coordinates_arr,
                    std::initializer_list<bool> is_vertical_arr);
        playField(const playField &play_field);
        playField& operator = (const playField& play_field);
        playField(playField && play_field) noexcept;
        playField& operator = (playField && play_field) noexcept;

        bool inField(size_t length, std::pair<size_t, size_t>coordinates, bool is_vertical);
        void addShip(size_t length, std::pair<size_t, size_t>coordinates, bool is_vertical);
        void Attack(std::pair<size_t, size_t> coordinates);
        shipManager getShipManager() const;
        void printField();
};