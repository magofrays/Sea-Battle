#include "saveLoadManager.h"

void saveLoadManager::openForRead(){
    infile.open(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file for reading.");
    }
}

void saveLoadManager::openForWrite(){
    outfile.open(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file for writing.");
    }
}

void saveLoadManager::write(const json& j){
    if (outfile.is_open()) {
        outfile << j.dump(4);
    } else {
        throw std::runtime_error("File not open for writing.");
    }
}

void saveLoadManager::read(json& j){
    if (infile.is_open()) {
        infile >> j;
    }else {
        throw std::runtime_error("File not open for reading.");
    }
}

saveLoadManager::~saveLoadManager(){
    if (infile.is_open()) {
        infile.close();
    }
    if (outfile.is_open()) {
        outfile.close();
    }
}