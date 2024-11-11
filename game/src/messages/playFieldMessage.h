#pragma once
#include "../playField.h"
#include "Message.h"

enum class fieldPosition{
    left,
    center,
    right
};

struct playFieldMessage: public Message{
    playField & info;
    fieldPosition position;
    playFieldMessage(playField & info, fieldPosition position): info(info), position(position){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<playFieldMessage>(*this);
    }
};