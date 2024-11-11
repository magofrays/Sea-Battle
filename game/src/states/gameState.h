#pragma once
#include "../utilities/vector2d.h"
#include "../messages/messageHandler.h"

class Game;
class gameState: public messageHandler{
    protected:
        messageHandler * handler;
        Game * game; 
    public:
        gameState(Game * game): game(game) {}
        void setGame(Game * game);
        virtual void execute() = 0;
        virtual ~gameState() {}

        virtual void Handle(std::unique_ptr<Message> message) = 0;
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};