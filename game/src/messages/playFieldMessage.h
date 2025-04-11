#ifndef SEABATTLE_PLAYFIELD_MESSAGE_H
#define SEABATTLE_PLAYFIELD_MESSAGE_H

#include "Message.h"
#include "../playField.h"
#include <string>

enum class fieldPosition
{
    left,
    center,
    right
};

struct playFieldMessage : public Message
{
    std::string field_name;
    playField *field;
    fieldPosition position;
    bool fog;
    bool draw_pointer;
    bool visible;
    playFieldMessage() : visible(false) {}
    playFieldMessage(std::string field_name, playField &field, fieldPosition position, bool fog, bool draw_pointer = false) : field_name(field_name), field(&field),
                                                                                                                              position(position), fog(fog), draw_pointer(draw_pointer), visible(true) {}
    std::unique_ptr<Message> clone()
    {
        return std::make_unique<playFieldMessage>(*this);
    }
};
#endif