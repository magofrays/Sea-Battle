#pragma once
#include "../humanPlayer.h"
#include "../botPlayer.h"
#include "gameState.h"
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"
#include "../IO/GUIInput.h"
#include "../IO/GUIOutput.h"

class Game: public messageHandler{
    gameState * state;
    messageHandler * handler;
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