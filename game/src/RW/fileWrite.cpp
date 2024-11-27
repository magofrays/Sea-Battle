#include "fileWrite.h"

fileWrite::fileWrite(std::string fname){
    writer.open(fname);
    if (!writer.is_open()) {
        throw std::runtime_error("Could not open file.");
    }
}

void fileWrite::write(const json& j){
    if (writer.is_open()){
        writer << j.dump(4);
    } 
    else {
        throw std::runtime_error("File not open for writing.");
    }
}

fileWrite::~fileWrite(){
    if (writer.is_open()) {
        writer.close();
    }
}
