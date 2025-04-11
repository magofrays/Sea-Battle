#ifndef SEABATTLE_GAMETRACKER_H
#define SEABATTLE_GAMETRACKER_H
#include "../states/Game.h"
#include "../messages/playFieldMessage.h"
#include "../messages/pointerMessage.h"
#include "../messages/textMessage.h"

template <typename gameOutput>
class gameTracker : public messageHandler
{
    gameOutput output;
    Game &game;
    messageHandler *handler;

public:
    gameTracker(Game &game);
    void update();
    void Handle(std::unique_ptr<Message> message);
    void setNext(messageHandler *handler);
};

template <typename gameOutput>
gameTracker<gameOutput>::gameTracker(Game &game) : game(game)
{
    game.setupGame(this);
}

template <typename gameOutput>
void gameTracker<gameOutput>::update()
{
    output.update();
}

template <typename gameOutput>
void gameTracker<gameOutput>::Handle(std::unique_ptr<Message> message)
{
    if (typeid(*message) == typeid(textMessage))
    {
        std::unique_ptr<textMessage> derivedPtr(static_cast<textMessage *>(message.release()));
        output.sendText(std::move(derivedPtr));
    }
    else if (typeid(*message) == typeid(playFieldMessage))
    {
        std::unique_ptr<playFieldMessage> derivedPtr(static_cast<playFieldMessage *>(message.release()));
        output.sendField(std::move(derivedPtr));
    }
    else if (typeid(*message) == typeid(pointerMessage))
    {
        std::unique_ptr<pointerMessage> derivedPtr(static_cast<pointerMessage *>(message.release()));
        output.sendPointer(std::move(derivedPtr));
    }
}

template <typename gameOutput>
void gameTracker<gameOutput>::setNext(messageHandler *handler)
{
    this->handler = handler;
}

#endif
