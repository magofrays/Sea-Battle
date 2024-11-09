#include "Game.h"

Game::Game(messageHandler * handler){
    state = std::make_shared<setupState>();
    state->setNext(handler);
    player.setNext(this);
}

Game::Game(std::shared_ptr<gameState> state, messageHandler * handler) : state(state){ // for testing probably
    state->setNext(handler);
    player.setNext(this);
}

void Game::setState(gameState & state){
    this->state = state;
    state->setGame(*this);
    
    this->setNext(*state);
}

void Game::execute(){
    state->execute();
}
template <typename T>
void Game::Handle(Message<T> message){
    if(std::is_same_v<T, Action>){
        if(message.info == Action::quit){
            running = false;
        }
        else{
            handler->Handle(message);
        }
    }
}

void Game::setNext(messageHandler * handler){
    this->handler = handler;
}