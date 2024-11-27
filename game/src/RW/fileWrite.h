#ifndef SEABATTLE_FILEWRITE_H
#define SEABATTLE_FILEWRITE_H

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class fileWrite{
private:
    std::ofstream writer;


public:
    fileWrite(std::string fname);

    void write(const json& j);

    ~fileWrite();
};

#endif
