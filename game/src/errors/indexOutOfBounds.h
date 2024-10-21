class indexOutOfBounds: public std::exception{
    int index;
    int max_index;
    std::string msg;

    public:
        indexOutOfBounds(int index, int max_index):index(index), max_index(max_index){
            msg = "Index is " + std::to_string(index) 
                    + ", but must be between 0 and " + std::to_string(max_index) + "!\n";
        }
        const char * what()  const noexcept override{
            return msg.c_str();
        }
};