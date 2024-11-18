#pragma once
#include "../playField.h"
#include "../messages/messageHandler.h"
#include "../messages/textMessage.h"
#include "../messages/keyMessage.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"

class gameOutput: public messageHandler{
    protected:
        messageHandler * handler = nullptr;
    public:
    //virtual void drawField(std::string field_name, playField & field, fieldPosition position, bool fog) = 0;
    //virtual void drawPointer(point2d pointer) = 0;
    virtual ~gameOutput() {}

    virtual void Handle(std::unique_ptr<Message> message) = 0;
    void setNext(messageHandler * handler){
        this->handler = handler;
    }
};