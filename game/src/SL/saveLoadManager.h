#include <nlohmann/json.hpp>
#include <fstream>
using json = nlohmann::json;

class saveLoadManager{
private:
    std::string filename;
    std::ifstream infile;
    std::ofstream outfile;

public:
    saveLoadManager(const std::string& fname) : filename(fname) {}

    void openForRead();

    void openForWrite();

    void write(const json& j);

    void read(json& j);

    ~saveLoadManager();
};
