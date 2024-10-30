#include "abilitiesManager.h"


abilitiesManager::abilitiesManager() {
    std::vector<std::shared_ptr<IAbility>> abilities;
    abilities.push_back(std::make_shared<scannerAbility>());
    abilities.push_back(std::make_shared<doubleDamageAbility>());
    abilities.push_back(std::make_shared<shellingAbility>());
    std::shuffle(abilities.begin(), abilities.end(), std::mt19937(std::random_device()()));
    for(auto ability: abilities){
        this->abilities.push(ability);
    }
}

void abilitiesManager::createRandomAbility(){
    std::mt19937 gen(std::random_device{}());
    int ability_index = gen() % 3;
    switch(ability_index){
        case 0:
            abilities.push(std::make_shared<scannerAbility>());
            break;
        case 1:
            abilities.push(std::make_shared<doubleDamageAbility>());
            break;
        case 2:
            abilities.push(std::make_shared<shellingAbility>());
            break;
    }
}

void abilitiesManager::applyAbility(Player * player){
    if(abilities.size()  <= 0){
        throw noAbilitiesException();
        }
    std::shared_ptr<IAbility> last_ability = abilities.front();
    last_ability->setPlayer(player);
    last_ability->apply();
    abilities.pop();
    

}
