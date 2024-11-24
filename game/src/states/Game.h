#pragma once
#include "../humanPlayer.h"
#include "../botPlayer.h"
#include "gameState.h"
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"
#include "../IO/gameInput.h"
#include "../IO/gameOutput.h"
#include "../states/setupFieldState.h"
#include "../RW/fileRW.h"

class Game: public messageHandler{
    gameState * state;
    messageHandler * handler;
    fileRW save_load;
    public:
        bool running = true;
        humanPlayer player;
        botPlayer bot;
        Game(messageHandler * handler);     
        void setState(gameState * state);
        void execute();
        ~Game();
        
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler * handler);

        void save();
        void load(); 
};