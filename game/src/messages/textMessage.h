#ifndef SEABATTLE_TEXT_POSITION_H
#define SEABATTLE_TEXT_POSITION_H

#include "Message.h"
#include <SDL2/SDL.h>

enum class textPosition{
    title,
    log,
};

struct textMessage: public Message{
    std::string msg = "";
    SDL_Color color = {255,255,255,255};
    textPosition position;

    textMessage() = default;
    textMessage(std::string msg, SDL_Color color, textPosition position):msg(msg), color(color), position(position){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<textMessage>(*this);
    }
};

#endif