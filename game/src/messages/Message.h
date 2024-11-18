#pragma once
#include "../utilities/vector2d.h"
struct Message{
    public:
    virtual std::unique_ptr<Message> clone() = 0;
    virtual ~Message() {}
};