#pragma once
#include "../utilities/vector2d.h"
#include "Message.h"

struct pointerMessage: public Message{
    box2d info;
    pointerMessage(box2d info): 
                info(info){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<pointerMessage>(*this);
    }
};