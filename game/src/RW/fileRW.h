#pragma once;
#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json

class fileRW{
private:
    std::fstream read_write;


public:
    fileRW(const std::string& fname);

    void write(const json& j);

    void read(json& j);

    ~fileRW();
};
