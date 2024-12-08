#ifndef SEABATTLE_GAMECONTROLLER_H
#define SEABATTLE_GAMECONTROLLER_H

#include <concepts>
#include <type_traits>
#include "../messages/messageHandler.h"
#include "../messages/textMessage.h"
#include "../messages/keyMessage.h"
#include "../states/Game.h"

class Game;


template<typename gameInput>
class gameController : public messageHandler {
    
    gameInput input;
    Game & game;
    messageHandler * handler;

    public:
        gameController(Game & game);
        void update();
        void Handle(std::unique_ptr<Message> message);
        void setNext(messageHandler* handler);
};

template<typename gameInput>
gameController<gameInput>::gameController(Game & game) : game(game)
    { 
    this->setNext(&game); 
    this->input.setNext(this);
    this->input.setControls();
}


template<typename gameInput>
void gameController<gameInput>::update(){
    input.update();
}

template<typename gameInput>
void gameController<gameInput>::Handle(std::unique_ptr<Message> message){
    if(typeid(*message) == typeid(keyMessage)){
        
        Message * msg = &(*message);
        keyMessage * key_msg = dynamic_cast<keyMessage*>(msg);
        switch(key_msg->info){
            case(Key::pointer_up):
                game.pointer.y += 1;
                return;
            
            case(Key::pointer_down):
                game.pointer.y -= 1;
                return;
            
            case(Key::pointer_right):
                game.pointer.x += 1;
                return;
            
            case(Key::pointer_left):
                game.pointer.x -= 1;
                return;

            case(Key::quit):
                game.running = false;
                return;
            
            case(Key::main_action):
                game.main_action();
                return;
            
            case(Key::extra_action_0):
                game.extra_action_0();
                return;

            case(Key::extra_action_1):
                game.extra_action_1();
                return;

            case(Key::save_action):
                game.save();
                handler->Handle(textMessage("You saved!", textColor::yellow, textPosition::log).clone());
                return;
            
            case(Key::load_action):
                try{
                    game.load();
                    handler->Handle(textMessage("You loaded!", textColor::yellow, textPosition::log).clone());
                }
                catch(std::runtime_error & e)
                { handler->Handle(textMessage(e.what(), textColor::red, textPosition::log).clone()); }
                
                catch(nlohmann::json_abi_v3_11_3::detail::parse_error & e)
                    { handler->Handle(textMessage("Error: Bad json structure! Create new save!", textColor::red, textPosition::log).clone()); }

                catch(nlohmann::json_abi_v3_11_3::detail::type_error & e){
                    { handler->Handle(textMessage("Error: Bad json structure! Create new save!", textColor::red, textPosition::log).clone()); }
                }
                return;
        }
    }
    handler->Handle(std::move(message));
}

template<typename gameInput>
void gameController<gameInput>::setNext(messageHandler * handler){
    this->handler = handler;
}




#endif
