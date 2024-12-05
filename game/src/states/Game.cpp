#include "Game.h"
#include "gameState.h"
#include "setupFieldState.h"
#include "setupShipState.h"
#include "playState.h"
#include "endGameState.h"
#include "../messages/textMessage.h"
#include "../RW/fileRead.h"
#include "../RW/fileWrite.h"
#include <iostream>

Game::Game() : pointer(player.pointer){
    this->running = true;
    state = new setupFieldState(this, handler); 
    setNext(state);
}

Game::Game(messageHandler * handler) : pointer(player.pointer){
    this->running = true;
    state = new setupFieldState(this, handler); 
    setHandlerToPlayers(handler);
    setNext(state);
}

void Game::setHandlerToPlayers(messageHandler * handler){
    player.setNext(handler);
    bot.setNext(handler);
}
void Game::setState(gameState * state){
    delete this->state;
    this->state = state;
    setNext(state);
}

void Game::update(){
    state->update();
}

void Game::main_action(){
    state->main_action();
}

void Game::extra_action_0(){
    state->extra_action_0();
}

void Game::extra_action_1(){
    state->extra_action_1();
}

void Game::save(){
    fileWrite save(seabattle::SAVE_DIR);
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
    json full_data;
    full_data["seabattle"] = data;
    full_data["hash_code"] = std::hash<std::string>{}(data.dump());
    save.write(full_data);
}

void Game::load(){
    bot.ship_manager = shipManager();
    player.ship_manager = shipManager();
    fileRead load(seabattle::SAVE_DIR);
    json full_data;
    load.read(full_data);
    json data = full_data["seabattle"];
    size_t hash_1 = std::hash<std::string>{}(data.dump());
    size_t hash_2 = full_data["hash_code"];
    if(hash_1 != hash_2){
        std::cout << hash_1 << " " << hash_2 << "\n";
        throw std::runtime_error("ERROR: Save data is corrupted! Create new save.");
    }
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

void Game::setNext(messageHandler * handler){
    this->handler = handler;
}


Game::~Game(){
    delete state;
}

