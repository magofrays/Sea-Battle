#ifndef SEABATTLE_GAMECONTROLLER_H
#define SEABATTLE_GAMECONTROLLER_H

#include <concepts>
#include <type_traits>
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"

class Game;

template<typename T>
concept messageHandlerDerived = std::is_base_of_v<messageHandler, T>;

template<messageHandlerDerived gameInput, messageHandlerDerived gameOutput>
class gameController : public messageHandler {
    Game & game;
    gameInput input;
    gameOutput output;
    messageHandler * handler;

    public:
        gameController(Game & game);
        void run();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler* handler);
};

#endif
