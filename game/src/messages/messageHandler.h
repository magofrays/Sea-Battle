#include "Message.h"
class messageHandler{
    template <typename T>
    virtual void Handle(Message<T> message) = 0;
    virtual void setNext(messageHandler * handler) = 0;
}