#pragma once
#include <string>

class invalidShipLength : public std::exception {
    int length;
    std::string msg;  

    public:
        invalidShipLength(int length) : length(length) {
            msg = "Ship length is " + std::to_string(length) + ", but must be between 1 and 4\n";
        }

        const char* what() const noexcept override {
            return msg.c_str(); 
        }
};