class inputException : public std::exception {
    std::string msg;  

    public:
        inputException() {
            msg = "Your input is wrong somewhere!\n";
        }

        const char* what() const noexcept override {
            return msg.c_str(); 
        }
};