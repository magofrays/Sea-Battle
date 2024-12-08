#pragma once
#include "../humanPlayer.h"
#include "../botPlayer.h"
#include "gameState.h"
#include "../messages/messageHandler.h"
#include "../messages/keyMessage.h"

class Game: public messageHandler{
    gameState * state;
    messageHandler * handler;
    public:
        bool running;
        point2d & pointer;
        box2d & pointer_area;
        humanPlayer player;
        botPlayer bot;
        
        Game(messageHandler * handler);     
        
        void setState(gameState * state);
        
        void update();
        void main_action();
        void extra_action_0();
        void extra_action_1();
        
        ~Game();
        
        void Handle(std::unique_ptr<Message> message){
            handler->Handle(std::move(message));
        }
        void setNext(messageHandler * handler);

        void save();
        void load(); 
};