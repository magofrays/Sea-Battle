#include "Game.h"
#include "gameState.h"
#include "../messages/textMessage.h"

Game::Game(messageHandler * handler){
    state = new setupFieldState(this); 
    state->setNext(handler);
    player.setNext(this);
    bot.setNext(this);
    setNext(state);
}

Game::Game(gameState * state, messageHandler * handler) : state(state){ // for testing probably
    setState(state);
    state->setNext(handler);
    player.setNext(this);
    bot.setNext(this);
    setNext(state);
}

void Game::setState(gameState * state){
    state->setNext(this->state->handler);
    delete this->state;
    this->state = state;
    setNext(state);
}

void Game::execute(){
    state->execute();
}

void Game::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        if(key_msg->info == Key::quit){
            running = false;
            return;
        }
    handler->Handle(std::move(message));
        
    }
}

void Game::setNext(messageHandler * handler){
    this->handler = handler;
}

Game::~Game(){
    delete state;
}

void Game::save(){
    
}