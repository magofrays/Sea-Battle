class invalidShipPosition: public std::exception{
    Ship ship;
    Ship other;
    std::string msg;
    public:
        invalidShipPosition(Ship ship, Ship other): ship(ship), other(other){
            msg = "Ship " + std::to_string(ship.getLen()) + " segments long, located " 
            + (ship.IsVertical() ? "vertically":"horizontally") + " at (" + std::to_string(ship.getCoor().first) + ", "
            + std::to_string(ship.getCoor().second) + "), touches another ship " + std::to_string(other.getLen()) 
            + " segments long, located " + (other.IsVertical() ? "vertically":"horizontally") + " at ("
            + std::to_string(other.getCoor().first) + ", " + std::to_string(other.getCoor().second) + ")\n";
            }
        const char* what() const noexcept override {
            return msg.c_str();
        }
};