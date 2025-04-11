#pragma once
#include "Message.h"
class messageHandler
{
public:
    virtual void Handle(std::unique_ptr<Message> message) = 0;
    virtual void setNext(messageHandler *handler) = 0;
};