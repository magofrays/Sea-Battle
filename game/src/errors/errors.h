#pragma once
#include "../utilities/vector2d.h"
class objectOutOfBounds : public std::exception
{
    point2d coordinates;
    std::string msg;

public:
    objectOutOfBounds(point2d coordinates) : coordinates(coordinates)
    {
        msg = "ERROR: Object located at (" + std::to_string(coordinates.x) +
              ", " + std::to_string(coordinates.y) + ") is out of bounds!\n";
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class invalidFieldSize : public std::exception
{
    std::string msg;
    int size_x;
    int size_y;

public:
    invalidFieldSize(int size_x, int size_y)
    {
        msg = "ERROR: Field size (" + std::to_string(size_x) + " ," + std::to_string(size_y) + ") is invalid!";
    }
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class invalidShipLength : public std::exception
{
    int length;
    std::string msg;

public:
    invalidShipLength(int length) : length(length)
    {
        msg = "ERROR: Ship length is " + std::to_string(length) + ", but must be between 1 and 4\n";
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class invalidShipPosition : public std::exception
{
    std::string msg;

public:
    invalidShipPosition()
    {
        msg = "ERROR: Ship intersects other ship\n";
    }
    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class noAbilitiesException : public std::exception
{
    std::string msg;

public:
    noAbilitiesException()
    {
        msg = "ERROR: There are no abilities in a queue!\n";
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};

class inputException : public std::exception
{
    std::string msg;

public:
    inputException()
    {
        msg = "ERROR: Your input is wrong somewhere!\n";
    }

    const char *what() const noexcept override
    {
        return msg.c_str();
    }
};