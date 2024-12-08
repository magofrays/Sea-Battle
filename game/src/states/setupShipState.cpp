#include "setupShipState.h"

setupShipState::setupShipState(Game * game, messageHandler * next, bool place_ships) : gameState(game), 
            field(game->player.play_field), pointer(game->player.pointer), pointer_area(game->player.pointer_area){
    this->handler = next;
    Handle(textMessage("Add ships!", textColor::yellow, textPosition::title).clone());
    if(place_ships){
        pointer = point2d(0, 0);
        game->player.callculateShips(ships);    
        game->bot.placeShipsRandomly(ships);
    }
    Handle(pointerMessage(pointer_area, pointer).clone());
    Handle(playFieldMessage("Your field", field, fieldPosition::center, false, true).clone());
}


bool setupShipState::enoughShips(){
    return !(ships[0] || ships[1] || ships[2] || ships[3]);
}

void setupShipState::update(){
    if(!enoughShips()){
        if(ships[3]){
            pointer_area.max_point = point2d(0, 3);
            length = 4;
        }
        else if(ships[2]){
            pointer_area.max_point = point2d(0, 2);
            length = 3;
        }
        else if(ships[1]){
            pointer_area.max_point = point2d(0, 1);
            length = 2;
        }
        else if(ships[0]){
            pointer_area.max_point = point2d(0, 0);
            length = 1;
        }
        if(!is_vertical){
            pointer_area.max_point = point2d(pointer_area.max_point.y, pointer_area.max_point.x);
        }
        if(!game->player.areaInField(pointer_area, pointer)){
            is_vertical = !is_vertical;
        }
        
    }
    else{
        this->end();
        
    }
}

void setupShipState::main_action(){
    try{
        game->player.placeShip(std::make_shared<Ship>(length, pointer, is_vertical));
        switch(length){
            case 4:
                ships[3]--;
                break;
            case 3:
                ships[2]--;
                break;
            case 2:
                ships[1]--;
                break;
            case 1:
                ships[0]--;
        }
        if(game->player.ship_manager.noFreeCells(game->player.play_field.getArea())){
            this->end();
        }
    }catch(invalidShipPosition & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    catch(objectOutOfBounds & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
}

void setupShipState::extra_action_0(){
    if(game->player.areaInField(box2d(pointer_area.max_point, point2d(pointer_area.max_point.y, pointer_area.max_point.x)), pointer)){
        is_vertical = !is_vertical;
    }
}

void setupShipState::extra_action_1(){
    game->player.placeShipsRandomly(ships);
    this->end();
}

void setupShipState::end(){
    game->setState(new playState(game, this->handler));
}


void setupShipState::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));
}


json & operator << (json & data, setupShipState & game_state){
    data["ships"][0] = game_state.ships[0];
    data["ships"][1] = game_state.ships[1];
    data["ships"][2] = game_state.ships[2];
    data["ships"][3] = game_state.ships[3];
    data["is_vertical"] = game_state.is_vertical;
    data["length"] = game_state.length;
    return data;
 }

json & operator >> (json & data, setupShipState & game_state){
    game_state.ships[0] = data["ships"][0];
    game_state.ships[1] = data["ships"][1];
    game_state.ships[2] = data["ships"][2];
    game_state.ships[3] = data["ships"][3];
    game_state.is_vertical = data["is_vertical"];
    game_state.length = data["length"];
    return data;
}