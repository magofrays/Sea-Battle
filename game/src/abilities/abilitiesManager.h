#ifndef SEABATTLE_ABILITIESMANAGER_H
#define SEABATTLE_ABILITIESMANAGER_H

#include <memory>
#include <queue>
#include "IAbility.h"

class abilitiesManager{
    std::queue <std::shared_ptr<IAbility>> abilities;
    public:
        abilitiesManager();
        void createRandomAbility();
        std::shared_ptr<IAbility> getAbility();
};

#endif

