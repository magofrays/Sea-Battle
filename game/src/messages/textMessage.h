#pragma once
#include "../utilities/vector2d.h"
#include "Message.h"

/*enum class textPosition{
    title,
    info,
    log,
};*/


struct textMessage: public Message{
    std::string info;
    point2d coordinates;
    //textPosition position;
    textMessage(std::string info, point2d coordinated):info(info), coordinates(coordinates){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<textMessage>(*this);
    }
};