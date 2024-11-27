#include "Game.h"
#include "gameState.h"
#include "setupFieldState.h"
#include "setupShipState.h"
#include "playState.h"
#include "endGameState.h"
#include "../messages/textMessage.h"
#include "../RW/fileRead.h"
#include "../RW/fileWrite.h"

Game::Game(messageHandler * handler){
    state = new setupFieldState(this, handler); 
    player.setNext(handler);
    bot.setNext(handler);
    setNext(state);
}

void Game::setState(gameState * state){
    //state->setNext(this->state->handler);
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
        if(key_msg->info == Key::save_action){
            this->save();
            handler->Handle(textMessage("You saved!", {255, 255, 0, 255}, textPosition::log).clone());
        }
        if(key_msg->info == Key::load_action){
            this->load();
            handler->Handle(textMessage("You loaded!", {255, 255, 0, 255}, textPosition::log).clone());
        }
    }
    handler->Handle(std::move(message));
}

void Game::setNext(messageHandler * handler){
    this->handler = handler;
}



void Game::save(){
    fileWrite save(std::string(seabattle::SAVE_DIR));
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
        data["humanPlayer"] << player;
        data["botPlayer"] << bot;
    }
    if(state_name == typeid(playState).name()){
        playState * tr_state = dynamic_cast<playState*>(this->state);
        data[state_name] << *tr_state;
        data["humanPlayer"] << player;
        data["botPlayer"] << bot;
    }
    if(state_name == typeid(endGameState).name()){
        endGameState * tr_state = dynamic_cast<endGameState *>(this->state);
        data[state_name] << *tr_state;
        data["humanPlayer"] << player;
        data["botPlayer"] << bot;
    }
    save.write(data);
}

void Game::load(){
    bot.ship_manager = shipManager();
    player.ship_manager = shipManager();
    fileRead load(std::string(seabattle::SAVE_DIR));
    json data;
    load.read(data);
    std::string state_name = data["state_name"];
    if(state_name == typeid(setupFieldState).name()){
        setupFieldState * new_state = new setupFieldState(this, this->state->handler);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
    if(state_name == typeid(setupShipState).name()){
        data["humanPlayer"] >> player;
        data["botPlayer"] >> bot;
        setupShipState * new_state = new setupShipState(this, this->state->handler, false);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
    if(state_name == typeid(playState).name()){
        data["humanPlayer"] >> player;
        data["botPlayer"] >> bot;
        playState * new_state = new playState(this, this->state->handler,  data[state_name]["round_number"]);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
    if(state_name == typeid(endGameState).name()){
        data["humanPlayer"] >> player;
        data["botPlayer"] >> bot;
        endGameState * new_state = new endGameState(this, this->state->handler, data[state_name]["lost"], data[state_name]["round_number"]);
        data[state_name] >> *new_state;
        this->setState(new_state);
    }
}

Game::~Game(){
    delete state;
}

