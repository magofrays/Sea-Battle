#include "setupShipState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"
#include "../utilities/settings.h"

setupShipState::setupShipState(Game * game) : gameState(game), 
            field(game->player.play_field), pointer(game->player.pointer){
    
    point2d sizes = game->player.play_field.getArea().max_point;
    int area = (sizes.x+1)*(sizes.y+1);
    int count = ceil(area * 0.2);
    int max_first = (area <= 100) ? 5 : ceil(count * 0.25);
    int max_second = (area <= 100) ? ceil(count * 0.5 / 2) : ceil(count * 0.4 / 2);
    int max_third = (area <= 100) ? ceil(count * 0.45 / 3) : ceil(count * 0.4 / 3);
    int max_fourth = (area <= 100) ? ceil(count * 0.26 / 4) : ceil(count * 0.31 / 4);

    for (int first = 1; first < max_first; first++) {
        for (int second = 0; second < max_second; second++) {
            for (int third = 0; third < max_third; third++) {
                for (int fourth = 0; fourth < max_fourth; fourth++) {
                    if (first + second * 2 + third * 3 + fourth * 4 == count) {
                        if (fourth <= third && third <= second && second <= first) {
                            single_decks = first;
                            double_decks = second;
                            three_decks = third;
                            four_decks = fourth;
                        }
                    }
                }
            }
        }
    }
    game->bot.placeShipsRandomly(single_decks, double_decks, three_decks, four_decks);
    //std::cout << single_decks << " " << double_decks << " " << three_decks << " " << four_decks << "\n";
}
bool setupShipState::enoughShips(){
    return !(single_decks || double_decks || three_decks || four_decks);
}
void setupShipState::execute(){
    if(!enoughShips()){
        pointer_area;
        if(four_decks){
            pointer_area.max_point = point2d(0, 3);
            length = 4;
        }
        else if(three_decks){
            pointer_area.max_point = point2d(0, 2);
            length = 3;
        }
        else if(double_decks){
            pointer_area.max_point = point2d(0, 1);
            length = 2;
        }
        else if(single_decks){
            pointer_area.max_point = point2d(0, 0);
            length = 1;
        }
        if(!is_vertical){
            pointer_area.max_point = point2d(pointer_area.max_point.y, pointer_area.max_point.x);
        }
        if(!shipInField(pointer_area, pointer)){
            is_vertical = !is_vertical;
        }
        Handle(textMessage("Add ships!", {255, 255, 0, 255}, textPosition::title).clone());
        Handle(pointerMessage(pointer_area, pointer).clone());
        Handle(playFieldMessage("Your field", field, fieldPosition::center, false, true).clone());
    }
    else{
        //this->end();
        Handle(playFieldMessage("Your field", field, fieldPosition::left, false, false).clone());
        Handle(playFieldMessage("Bot field", game->bot.play_field, fieldPosition::right, false, false).clone());
    }
    
    
}

bool setupShipState::shipInField(box2d area, point2d coordinates){
    area.min_point += coordinates;
    area.max_point += coordinates;
    return field.getArea().contains(area);
}

void setupShipState::placeShip(){
    try{
        game->player.placeShip(std::make_shared<Ship>(length, pointer, is_vertical));
        switch(length){
            case 4:
                four_decks--;
                break;
            case 3:
                three_decks--;
                break;
            case 2:
                double_decks--;
                break;
            case 1:
                single_decks--;
        }
        if(game->player.ship_manager.noFreeCells(game->player.play_field.getArea())){
            this->end();
        }
    }catch(invalidShipPosition & e){
        Handle(textMessage(e.what(), {255, 0, 0}, textPosition::log).clone());
    }
    catch(objectOutOfBounds & e){
        Handle(textMessage(e.what(), {255, 0, 0}, textPosition::log).clone());
    }
}

void setupShipState::Handle(std::unique_ptr<Message> message){
    
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case Key::pointer_up:
                if(shipInField(pointer_area, pointer + point2d(0, 1)))
                    game->player.pointer += point2d(0, 1);
                    break;

            case Key::pointer_down:
                if(shipInField(pointer_area, pointer - point2d(0, 1)))
                    game->player.pointer -= point2d(0, 1);
                    break;
            case Key::pointer_right:
                if(shipInField(pointer_area, pointer + point2d(1, 0)))
                    game->player.pointer += point2d(1, 0);
                    break;
                
            case Key::pointer_left:
                if(shipInField(pointer_area, pointer - point2d(1, 0)))
                    game->player.pointer -= point2d(1, 0);
                    break;
                
            case Key::main_action:
                this->placeShip();
                break;
            case Key::extra_action_0:
                if(shipInField(box2d(pointer_area.max_point, point2d(pointer_area.max_point.y, pointer_area.max_point.x)), pointer))
                    is_vertical = !is_vertical;
                break;
            case Key::extra_action_1:
                game->player.placeShipsRandomly(single_decks, double_decks, three_decks, four_decks);
                single_decks = 0; double_decks = 0; three_decks = 0; four_decks = 0;
                this->end();
                break;
                
            default:
                break;
        }
    }
    else{
        handler->Handle(std::move(message));
    }
}
