#pragma once
#include "../playField.h"

class consoleDrawer{
    public:
        consoleDrawer() = default;
        void drawField(playField & field, shipManager & ship_manager);
        void drawPlayerField(playField & field,  shipManager & ship_manager);
    
};
