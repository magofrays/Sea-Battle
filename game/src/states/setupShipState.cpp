#include "setupShipState.h"
#include "../messages/keyMessage.h"
#include "../messages/textMessage.h"
#include "setupShipState.h"
#include "../messages/playFieldMessage.h"
#include "errors/errors.h"
#include "../utilities/settings.h"

setupShipState::setupShipState(Game * game) : gameState(game), 
            field(game->player.play_field), pointer(game->player.pointer){
    box2d sizes = game->player.play_field.getArea();
    int area = sizes.max_point.x*sizes.min_point.y;
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
}

void setupShipState::execute(){
    Handle(textMessage("Add ships!", {255, 255, 0, 255}, textPosition::title).clone());
    Handle(pointerMessage(box2d(), pointer).clone());
    Handle(playFieldMessage("Your field", field, fieldPosition::center, false, true).clone());
}

void setupShipState::Handle(std::unique_ptr<Message> message){
    
    if(typeid(*message) == typeid(keyMessage)){
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case Key::pointer_up:
                game->player.pointer += point2d(0, 1);
                break;
            case Key::pointer_down:
                game->player.pointer -= point2d(0, 1);
                break;
            case Key::pointer_right:
                game->player.pointer += point2d(1, 0);
                break;
            case Key::pointer_left:
                game->player.pointer -= point2d(1, 0);
                break;
            case Key::main_action:
                //this->end();
                break;
            case Key::extra_action:
                is_vertical = !is_vertical;
            default:
                break;
        }
    }
    else{
        handler->Handle(std::move(message));
    }
}
