#include "fileRW.h"

fileRW::fileRW(std::string fname){
    read_write.open(fname, std::ios_base::in | std::ios_base::out);
    if (!read_write.is_open()) {
        throw std::runtime_error("Could not open file.");
    }
}

void fileRW::write(const json& j){
    if (read_write.is_open()) {
        read_write.clear();
        read_write.seekp(0);
        read_write << j.dump(1);
        read_write.flush();
    } 
    else {
        throw std::runtime_error("File not open for writing.");
    }
}

void fileRW::read(json& j){
    if (read_write.is_open()) {
        read_write.seekg(0);
        read_write >> j;
    }
    else {
        throw std::runtime_error("File not open for reading.");
    }
}

fileRW::~fileRW(){
    if (read_write.is_open()) {
        read_write.close();
    }
}