#include "Player.h"
#include <random>
#include <iostream>

void Player::placeShipsRandomly(int ships[4]){
    int bot_ships[4] = {ships[0], ships[1], ships[2], ships[3]};
    std::mt19937 gen(std::random_device{}());
    box2d field_area = play_field.getArea();
    point2d field_size = field_area.max_point;
    while(bot_ships[0] || bot_ships[1] || bot_ships[2] || bot_ships[3]){
        bool is_vertical = (gen()%2 == 0);
        int x = gen()%(field_size.x+1); 
        int y = gen()%(field_size.y+1);
        int length;
        if(bot_ships[3]){
            length = 4;
        }
        else if(bot_ships[2]){
            length = 3;
        }
        else if(bot_ships[1]){
            length = 2;
        }
        else if(bot_ships[0]){
            length = 1;
        }
        bool placed = false;
        for(int i = 0; i != field_size.x+1; i++){
            for(int j = 0; j != field_size.y+1; j++){

                    Ship ship(length, {(x+i)%(field_size.x+1), (y+j)%(field_size.y+1)}, is_vertical);
                    box2d ship_area = ship.getArea();
                    if(play_field.getArea().contains(ship_area) && !ship_manager.shipIntersection(ship_area)){
                        this->placeShip(std::make_shared<Ship>(ship));
                        switch(length){
                            case 4:
                                bot_ships[3]--;
                                break;
                            case 3:
                                bot_ships[2]--;
                                break;
                            case 2:
                                bot_ships[1]--;
                                break;
                            case 1:
                                bot_ships[0]--;
                        }
                        if(ship_manager.noFreeCells(field_area)){
                            return;
                        }
                        placed = true;
                        break;
                    }
                if(placed) break;
            }
            if(placed) break;
        }
    }
}

void Player::callculateShips(int ships[4]){
    point2d sizes = play_field.getArea().max_point;
    int area = (sizes.x+1)*(sizes.y+1);
    int count = ceil(area * 0.2);
    int max_first = (area <= 100) ? 5 : ceil(count * 0.25);
    int max_second = (area <= 100) ? ceil(count * 0.5 / 2) : ceil(count * 0.4 / 2);
    int max_third = (area <= 100) ? ceil(count * 0.45 / 3) : ceil(count * 0.4 / 3);
    int max_fourth = (area <= 100) ? ceil(count * 0.26 / 4) : ceil(count * 0.31 / 4);

    for (int first = 1; first < max_first; first++) {
        for (int second = 0; second < max_second; second++) {
            for (int third = 0; third < max_third; third++) {
                for (int fourth = 0; fourth < max_fourth; fourth++) {
                    if (first + second * 2 + third * 3 + fourth * 4 == count) {
                        if (fourth <= third && third <= second && second <= first) {
                            ships[0] = first;
                            ships[1] = second;
                            ships[2] = third;
                            ships[3] = fourth;
                        }
                    }
                }
            }
        }
    }
}

json & operator << (json & data, Player & player){
    data["ship_manager"] = player.ship_manager.toJson();
    data["play_field"] = player.play_field.toJson();
    return data;
}

json & operator >> (json & data, Player & player){
    player.ship_manager = shipManager(data.at("ship_manager"));
    player.play_field = playField(data.at("play_field"));
    player.play_field.loadShips(player.ship_manager);
    return data;
}