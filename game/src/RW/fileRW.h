#ifndef SEABATTLE_FILERW_H
#define SEABATTLE_FILERW_H

#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class fileRW{
private:
    std::fstream read_write;


public:
    fileRW(std::string fname);

    void write(const json& j);

    void read(json& j);

    ~fileRW();
};

#endif
