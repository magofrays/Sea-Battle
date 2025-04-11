#include "fileRead.h"

fileRead::fileRead(std::string fname)
{
    reader.open(fname);
    if (!reader.is_open())
    {
        throw std::runtime_error("Could not open file.");
    }
}

void fileRead::read(json &j)
{
    if (reader.is_open())
    {
        reader >> j;
    }
    else
    {
        throw std::runtime_error("File not open for reading.");
    }
}

fileRead::~fileRead()
{
    if (reader.is_open())
    {
        reader.close();
    }
}