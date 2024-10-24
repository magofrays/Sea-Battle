#pragma once
#include "../playField.h"
#include "errors/indexOutOfBounds.h"
#include "errors/invalidShipLength.h"
#include "errors/objectOutOfBounds.h"
#include "errors/inputException.h"
#include "errors/invalidShipPosition.h"
#include "errors/invalidFieldSize.h"
class inputManager{
    public:
        inputManager() = default;
        std::istream& inputShip(std::istream& in, Ship& ship);
        std::istream& inputPlayField(std::istream& in, playField & playField);
};