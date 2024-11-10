#pragma once
#include "../playField.h"
#include "Message.h"

struct playFieldMessage: public Message{
    playField & info;   
    std::unique_ptr<Message> clone(){
        return std::make_unique<playFieldMessage>(*this);
    }
};