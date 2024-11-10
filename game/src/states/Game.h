#pragma once
#include "../humanPlayer.h"
#include "gameState.h"
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"
#include "../IO/gameInput.h"
#include "../IO/gameOutput.h"
#include "../states/setupFieldState.h"

class Game: public messageHandler{
    std::shared_ptr<gameState> state;
    messageHandler * handler;
    
    public:
        bool running = true;
        humanPlayer player;
        
        Game(messageHandler * handler);
        Game(std::shared_ptr<gameState> state, messageHandler * handler);
        void Game::setState(gameState & state);
        void execute();
        
        template <typename T>
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);

};