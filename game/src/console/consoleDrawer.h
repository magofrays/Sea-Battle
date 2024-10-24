#pragma once
#include "../playField.h"

class consoleDrawer{
    public:
        consoleDrawer() = default;
        void drawField(playField & field);
        void drawPlayerField(playField & field);
    
};
