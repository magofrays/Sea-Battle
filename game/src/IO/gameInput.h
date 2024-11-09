#include "../messages/messageHandler.h"
class gameInput: public messageHandler{
    messageHandler * handler;
    public:
        virtual Message update() = 0;
        
        template <typename T>
        virtual void Handle(Message<T> message) = 0;
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
}