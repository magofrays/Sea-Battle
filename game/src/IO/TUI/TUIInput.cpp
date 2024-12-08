#include "TUIInput.h"
#include "../../utilities/settings.h"
#include "../../RW/controlReader.h"
#include "../../messages/textMessage.h"
#include <iostream>

void TUIInput::setControls(){
    try{
        controls = controlReader()();
        return;
    }catch(std::invalid_argument & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    catch(nlohmann::json_abi_v3_11_3::detail::parse_error & e){
        Handle(textMessage("Error: Bad json structure in controls!", textColor::red, textPosition::log).clone());
    }
    catch(nlohmann::json_abi_v3_11_3::detail::type_error & e){
        Handle(textMessage("Error: Bad json structure in controls!", textColor::red, textPosition::log).clone());
    }
    catch(std::runtime_error & e){
        Handle(textMessage(e.what(), textColor::red, textPosition::log).clone());
    }
    controls = controlReader().getDefaultControls();
    Handle(textMessage("Default controls initialized!", textColor::red, textPosition::log).clone());
}

void TUIInput::update(){                                                                                                                                                                           
    std::string input;
    std::getline(std::cin, input);
    if(controls.contains(input)){
        Handle(keyMessage(controls[input]).clone());
    }
}

void TUIInput::Handle(std::unique_ptr<Message> message){
    handler->Handle(std::move(message));
}

void TUIInput::setNext(messageHandler * handler){
    this->handler = handler;
}