#ifndef SEABATTLE_TEXT_POSITION_H
#define SEABATTLE_TEXT_POSITION_H

#include "Message.h"
#include <SDL2/SDL.h>

enum class textPosition
{
    title,
    log,
};

enum class textColor
{
    red,
    yellow,
    purple,
    green,
    white,
    blue,
    black
};

struct textMessage : public Message
{
    std::string msg = "";
    textColor color = textColor::white;
    textPosition position;

    textMessage() = default;
    textMessage(std::string msg, textColor color, textPosition position) : msg(msg), color(color), position(position) {}
    std::unique_ptr<Message> clone()
    {
        return std::make_unique<textMessage>(*this);
    }
};

#endif