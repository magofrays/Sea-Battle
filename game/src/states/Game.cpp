#include "Game.h"
#include "gameState.h"
#include "setupFieldState.h"
#include "setupShipState.h"
#include "playState.h"
#include "../messages/textMessage.h"

Game::Game(messageHandler * handler) : save_load(std::string(seabattle::SAVE_DIR)){
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
    if(state_name == typeid(setupFieldState).name()){
        setupFieldState * tr_state = dynamic_cast<setupFieldState*>(this->state);
        data[state_name] << *tr_state;
    }
    if(state_name == typeid(setupShipState).name()){
        setupShipState * tr_state = dynamic_cast<setupShipState*>(this->state);
        data[state_name] << *tr_state;
    }
    if(state_name == typeid(playState).name()){
        playState * tr_state = dynamic_cast<playState*>(this->state);
        data[state_name] << *tr_state;
    }
    //data["humanPlayer"] << player;
    //data["botPlayer"] << bot;
    save_load.write(data);
}

void Game::load(){
    json data;
    save_load.read(data);
    std::string state_name = data["state_name"];
    //data["humanPlayer"] >> player;
    //data["botPlayer"] >> bot;
    if(state_name == typeid(setupFieldState).name()){
        setupFieldState * new_state = new setupFieldState(this);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
    if(state_name == typeid(setupShipState).name()){
        setupShipState * new_state = new setupShipState(this);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
    if(state_name == typeid(playState).name()){
        playState * new_state = new playState(this);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }

}

Game::~Game(){
    delete state;
}

