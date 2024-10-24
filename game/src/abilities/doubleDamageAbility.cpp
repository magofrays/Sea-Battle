#include "doubleDamageAbility.h"

doubleDamageAbility::doubleDamageAbility(std::pair<int, int> coordinates) : coordinates(coordinates){}
void doubleDamageAbility::setCoordinates(std::pair<int, int> coordinates){
    this->coordinates = coordinates;
}
void doubleDamageAbility::apply(playField & play_field, shipManager & ship_manager){
    std::cout << "Double damage ability applied!\n";
    play_field.getSegmentOrAttack(coordinates, true, ship_manager);
    play_field.getSegmentOrAttack(coordinates, true, ship_manager);
}
