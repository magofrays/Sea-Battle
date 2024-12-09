#include "TUIInput.h"
#include "../../utilities/settings.h"
#include "../../messages/textMessage.h"
#include <iostream>
#include <unistd.h>

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
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    if (!FD_ISSET(0, &fds)) {
        return;                                                 
    }                                                                                                                                                                             
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