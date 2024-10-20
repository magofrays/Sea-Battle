#include <string>
class shipLengthException{
    int length;
    public:
        shipLengthException(int length):length(lengh){}
        const char * what(){
            std::string msg = "Your ship length is " + std::to_string(length) 
                + " but must be between 1 and 4\n";
            return msg.c_str();
        }
}