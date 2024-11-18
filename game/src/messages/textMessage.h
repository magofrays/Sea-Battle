#pragma once
#include "../utilities/vector2d.h"
#include "Message.h"
#include "../IO/gameOutput.h"
#include <SDL2/SDL.h>

enum class textPosition{
    title,
    log,
};
 // why so many structs if i can put in textMessage struct
struct Text{
    std::string msg = "";
    SDL_Color color = {255,255,255,255};
    Text() = default;
    Text(std::string msg, SDL_Color color) : msg(msg), color(color){}
};

struct textMessage: public Message{
    Text info;
    textPosition position;
    textMessage(std::string msg, SDL_Color color, textPosition position):info(msg, color), position(position){}
    std::unique_ptr<Message> clone(){
        return std::make_unique<textMessage>(*this);
    }
};