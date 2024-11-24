#include "Game.h"
#include "gameState.h"
#include "setupFieldState.h"
#include "setupShipState.h"
#include "playState.h"
#include "../messages/textMessage.h"

Game::Game(messageHandler * handler){
    save_load(seabattle::SAVE_DIR);
    state = new setupFieldState(this); 
    state->setNext(handler);
    player.setNext(handler);
    bot.setNext(handler);
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
    }
    handler->Handle(std::move(message));
}

void Game::setNext(messageHandler * handler){
    this->handler = handler;
    player.setNext(handler);
    bot.setNext(handler);
}



void Game::save(){
    json data;
    std::string state_name = typeid(*state).name();
    data["state_name"] = state_name;
    switch state_name{
        case typeid(setupFieldState).name():
            setupFieldState * tr_state = dynamic_cast<setupFieldState*>(this->state);
            data[state_name] << *tr_state;
            break;
        case typeid(setupShipState).name():
            setupShipState * tr_state = dynamic_cast<setupShipState*>(this->state);
            data[state_name] << *tr_state;
            break;
        case typeid(playState).name():
            playState * tr_state = dynamic_cast<playState*>(this->state);
            data[state_name] << *tr_state;
            break;
    }
    data["humanPlayer"] << player;
    data["botPlayer"] << bot;
    save_load.write(data);
}

void Game::load(){
    json data;
    save_load.read(data);
    std::string state_name = data["state_name"];
    data["humanPlayer"] >> player;
    data["botPlayer"] >> bot;
    switch state_name{
        case typeid(setupFieldState).name():
            setupFieldState * new_state = new setupFieldState(this);
            data[state_name] >> new_state;
            this->setState(new_state);
            break;
        case typeid(setupShipState).name():
            setupFieldState * new_state = new setupShipState(this);
            data[state_name] >> *new_state;
            this->setState(new_state);
            break;
        case typeid(playState).name():
            setupFieldState * new_state = new playState(this);
            data[state_name] >> *new_state;
            this->setState(new_state);
            break;
    }

}

Game::~Game(){
    delete state;
}

