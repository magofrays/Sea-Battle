#pragma once
#include "../playField.h"
#include "Message.h"

enum class fieldPosition{
    left,
    center,
    right
};

struct playFieldMessage: public Message{
    std::string field_name;
    playField & info;
    fieldPosition position;
    bool fog;
    playFieldMessage(std::string field_name, playField & info, fieldPosition position, bool fog): field_name(field_name), info(info), 
                                                                                            position(position), fog(fog){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<playFieldMessage>(*this);
    }
};