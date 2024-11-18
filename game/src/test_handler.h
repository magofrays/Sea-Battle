#include "messages/messageHandler.h"
#include "messages/keyMessage.h"

class test_handler: public messageHandler{
    messageHandler * handler = nullptr;
    public:
        bool running = true;
    void setNext(messageHandler * handler){
        this->handler = handler;
    }
    void Handle(std::unique_ptr<Message> message){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        if(key_msg->info == Key::main_action){
            running = false;
            return;
        }   
    }
};