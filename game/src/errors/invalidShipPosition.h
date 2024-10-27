class invalidShipPosition: public std::exception{
    std::string msg;
    public:
        invalidShipPosition(){
                msg = "Ship intersects other ship\n";
            }
        const char* what() const noexcept override {
            return msg.c_str();
        }
};