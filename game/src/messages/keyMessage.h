#pragma once
#include "../utilities/vector2d.h"
#include "Message.h"

enum class Key{
        pointer_left,
        pointer_right,
        pointer_up,
        pointer_down,
        main_action,
        extra_action_0,
        extra_action_1,
        quit,
        save_action,
        load_action,
        null
    };

struct keyMessage: public Message{
    Key info;   
    keyMessage(Key info): info(info){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<keyMessage>(*this);
    }
};