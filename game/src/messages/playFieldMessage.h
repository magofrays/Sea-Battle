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
    bool draw_pointer;
    playFieldMessage(std::string field_name, playField & info, fieldPosition position, bool fog, bool draw_pointer = false): field_name(field_name), info(info), 
                                                                                            position(position), fog(fog), draw_pointer(draw_pointer){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<playFieldMessage>(*this);
    }
};