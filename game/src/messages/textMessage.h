#pragma once
#include "../utilities/vector2d.h"
#include "Message.h"

struct textMessage: public Message{
    std::string info;   
    textMessage(std::string info):info(info){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<textMessage>(*this);
    }
};