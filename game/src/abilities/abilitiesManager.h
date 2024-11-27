#ifndef SEABATTLE_ABILITIESMANAGER_H
#define SEABATTLE_ABILITIESMANAGER_H

#include <memory>
#include <deque>
#include "IAbility.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class abilitiesManager{
    std::deque <std::shared_ptr<IAbility>> abilities;
    public:
        abilitiesManager();
        abilitiesManager(const json & data);
        void createRandomAbility();
        std::shared_ptr<IAbility> getAbility();
        json toJson();
};

#endif

