#ifndef SEABATTLE_FILEREAD_H
#define SEABATTLE_FILEREAD_H

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class fileRead{
private:
    std::ifstream reader;


public:
    fileRead(std::string fname);

    void read(json& j);

    ~fileRead();
};

#endif
