#pragma once
#include "../playField.h"
#include "../messages/messageHandler.h"
#include "../messages/textMessage.h"
#include "../messages/keyMessage.h"
#include "../messages/playFieldMessage.h"

class gameOutput: public messageHandler{
    protected:
        messageHandler * handler = nullptr;
    public:
    virtual void drawField(playField & field, fieldPosition position) = 0;
    virtual void drawPointer(point2d pointer) = 0;
    virtual void drawText(point2d coordinates, std::string text) = 0;
    virtual ~gameOutput() {}

    virtual void Handle(std::unique_ptr<Message> message) = 0;
    void setNext(messageHandler * handler){
        this->handler = handler;
    }
};