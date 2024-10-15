#include "doubleDamageAbility.h"

doubleDamageAbility::doubleDamageAbility(std::pair<int, int> coordinates) : coordinates(coordinates){}
void doubleDamageAbility::setCoordinates(std::pair<int, int> coordinates){
    this->coordinates = coordinates;
}
void doubleDamageAbility::apply(playField & play_field){
    play_field.Attack(coordinates);
    play_field.Attack(coordinates);
}
