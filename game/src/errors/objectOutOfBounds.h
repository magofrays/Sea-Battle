class objectOutOfBounds : public std::exception {
    std::pair<int, int> coordinates;
    std::string msg;
    public:
        objectOutOfBounds(std::pair<int, int> coordinates) : coordinates(coordinates) {
            msg = "Object located at (" + std::to_string(coordinates.first) +
                ", " + std::to_string(coordinates.second) + ") is out of bounds!\n";
        }

        const char * what() const noexcept override {
            return msg.c_str();
        }
};
