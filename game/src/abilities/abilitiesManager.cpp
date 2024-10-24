#include "abilitiesManager.h"

abilitiesManager::abilitiesManager() {
    abilities.push_back(std::make_unique<scannerAbility>());
    abilities.push_back(std::make_unique<doubleDamageAbility>());
    abilities.push_back(std::make_unique<shellingAbility>());
    std::shuffle(abilities.begin(), abilities.end(), std::mt19937(std::random_device()()));
}

void abilitiesManager::createRandomAbility(){
    std::mt19937 gen(std::random_device{}());
    int ability_index = gen() % 3;
    switch(ability_index){
        case 0:
            abilities.push_back(std::make_unique<scannerAbility>());
            break;
        case 1:
            abilities.push_back(std::make_unique<doubleDamageAbility>());
            break;
        case 2:
            abilities.push_back(std::make_unique<shellingAbility>());
            break;
    }
}

void abilitiesManager::applyAbility(playField & play_field, shipManager & ship_manager){
    if(abilities.size() > 0){
        auto & lastAbility = abilities.back();
        lastAbility->apply(play_field, ship_manager);
        abilities.pop_back();
    }
}
