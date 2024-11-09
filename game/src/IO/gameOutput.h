#include "../playField.h"
#include "../messages/messageHandler.h"

class gameOutput: public messageHandler{
    messageHandler * handler = nullptr;
    public:
    virtual void drawField(point2d coordinates, playField & field) = 0;
    virtual void drawPointer(point2d & pointer) = 0;
    virtual void drawText(std::string text) = 0;
    virtual ~gameOutput {}

    template <typename T>
    virtual void Handle(Message<T> message) = 0;
    void setNext(messageHandler & handler){
        this->handler = handler;
    }
}