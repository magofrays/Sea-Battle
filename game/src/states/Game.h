#pragma once
#include "../humanPlayer.h"
#include "gameState.h"
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"
#include "../IO/gameInput.h"
#include "../IO/gameOutput.h"
#include "../states/setupFieldState.h"

class Game: public messageHandler{
    gameState * state;
    messageHandler * handler;
    
    public:
        bool running = true;
        humanPlayer player;
        
        Game(messageHandler * handler);
        Game(gameState * state, messageHandler * handler);
        void setState(gameState * state);
        void execute();
        ~Game();
        
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);
        
};