#pragma once
#include "../playField.h"
#include "../messages/messageHandler.h"

class gameOutput: public messageHandler{
    protected:
        messageHandler * handler = nullptr;
    public:
    virtual void drawField(point2d coordinates, playField & field) = 0;
    virtual void drawPointer(point2d & pointer) = 0;
    virtual void drawText(std::string text) = 0;
    virtual ~gameOutput() {}

    virtual void Handle(std::unique_ptr<Message> message) = 0;
    void setNext(messageHandler * handler){
        this->handler = handler;
    }
};