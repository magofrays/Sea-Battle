class invalidFieldSize: public std::exception{
    std::string msg;
    public:
        invalidFieldSize(){
            msg = "Field size is below 1!\n";
        }
        const char * what()  const noexcept override{
            return msg.c_str();
        }
};