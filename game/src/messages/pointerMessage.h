#ifndef SEABATTLE_POINTER_MESSAGE_H
#define SEABATTLE_POINTER_MESSAGE_H

#include "Message.h"
#include "../utilities/vector2d.h"

struct pointerMessage: public Message{
    box2d area;
    point2d coordinates;
    pointerMessage() = default;
    pointerMessage(box2d area, point2d coordinates): 
                area(area), coordinates(coordinates){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<pointerMessage>(*this);
    }
};

#endif