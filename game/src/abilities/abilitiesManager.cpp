#include "abilitiesManager.h"
#include "scannerAbility.h"
#include "shellingAbility.h"
#include "doubleDamageAbility.h"
#include <random>
#include "../errors/errors.h"

abilitiesManager::abilitiesManager() {
    std::vector<std::shared_ptr<IAbility>> abilities;
    abilities.push_back(std::make_shared<scannerAbility>());
    abilities.push_back(std::make_shared<doubleDamageAbility>());
    abilities.push_back(std::make_shared<shellingAbility>());
    std::shuffle(abilities.begin(), abilities.end(), std::mt19937(std::random_device()()));
    for(auto ability: abilities){
        this->abilities.push_back(ability);
    }
}

abilitiesManager::abilitiesManager(const json & data){
    int size = data["size"];
    for(int i = 0; i != size; i++){
        std::string ability_name = data.at("abilities")[i];
        if(ability_name == typeid(scannerAbility).name()){
            abilities.push_back(std::make_shared<scannerAbility>());
        }
        else if(ability_name == typeid(shellingAbility).name()){
            abilities.push_back(std::make_shared<shellingAbility>());
        }
        else if(ability_name == typeid(doubleDamageAbility).name()){
            abilities.push_back(std::make_shared<doubleDamageAbility>());
        }
    }
}

void abilitiesManager::createRandomAbility(){
    std::mt19937 gen(std::random_device{}());
    int ability_index = gen() % 3;
    switch(ability_index){
        case 0:
            abilities.push_back(std::make_shared<scannerAbility>());
            break;
        case 1:
            abilities.push_back(std::make_shared<doubleDamageAbility>());
            break;
        case 2:
            abilities.push_back(std::make_shared<shellingAbility>());
            break;
    }
}

std::shared_ptr<IAbility> abilitiesManager::getAbility(){
    if(abilities.size()  <= 0){
        throw noAbilitiesException();
        }
    std::shared_ptr<IAbility> last_ability = abilities.front();
    abilities.pop_front();
    return last_ability;
}

json abilitiesManager::toJson(){
    json data;
    data["size"] = abilities.size();
    for(auto ability: abilities){
        IAbility * abil = &(*ability);
        std::string abil_name = typeid(*abil).name();
        if(abil_name == typeid(scannerAbility).name()){
            data["abilities"].push_back(abil_name);
        }
        else if(abil_name == typeid(shellingAbility).name()){
            data["abilities"].push_back(abil_name);
        }
        else if(abil_name == typeid(doubleDamageAbility).name()){
            data["abilities"].push_back(abil_name);
        }

    }
    return data;
}
