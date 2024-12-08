#ifndef SEABATTLE_CONTROL_READER
#define SEABATTLE_CONTROL_READER

#include <map>
#include "../messages/keyMessage.h"
#include "fileRead.h"

class controlReader{
    std::map<std::string, Key> default_controls;
    public:
    controlReader(){
        default_controls["W"] = Key::pointer_down;
        default_controls["A"] = Key::pointer_left;
        default_controls["S"] = Key::pointer_up;
        default_controls["D"] = Key::pointer_right;
        default_controls["Return"] = Key::main_action;
        default_controls["E"] = Key::extra_action_0;
        default_controls["Q"] = Key::extra_action_1;
        default_controls["1"] = Key::save_action;
        default_controls["2"] = Key::load_action;
        default_controls["Escape"] = Key::quit;
    }

    Key getKeyFromString(const std::string& keyStr) {
        if (keyStr == "pointer_down") return Key::pointer_down;
        if (keyStr == "pointer_left") return Key::pointer_left;
        if (keyStr == "pointer_up") return Key::pointer_up;
        if (keyStr == "pointer_right") return Key::pointer_right;
        if (keyStr == "main_action") return Key::main_action;
        if (keyStr == "extra_action_0") return Key::extra_action_0;
        if (keyStr == "extra_action_1") return Key::extra_action_1;
        if (keyStr == "save_action") return Key::save_action;
        if (keyStr == "load_action") return Key::load_action;
        if (keyStr == "quit") return Key::quit;
        throw std::invalid_argument("Error: Unknown key: " + keyStr);
    }

    std::map<std::string, Key> operator()(){
        std::map<std::string, Key> controls;
        json controls_data;
        fileRead reader(seabattle::CONTROL_DIR);
        reader.read(controls_data);
        for (auto& [keyStr, valueStr] : controls_data.items()) {
            if(controls.contains(valueStr)){
                throw std::invalid_argument("Error: Value '" + std::string(valueStr) + "' points to two keys!");
            }
            controls[valueStr] = getKeyFromString(keyStr);
        }
        if(default_controls.size() != controls.size()){
            throw std::invalid_argument("Error: Some keys are not initialized!");
        }
        return controls;
    }

    std::map<std::string, Key> getDefaultControls(){
        return default_controls;
    }
};

#endif