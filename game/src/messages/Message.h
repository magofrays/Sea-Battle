#ifndef SEABATTLE_MESSAGE_H
#define SEABATTLE_MESSAGE_H
#include <memory>

struct Message
{
public:
    virtual std::unique_ptr<Message> clone() = 0;
    virtual ~Message() {}
};

#endif