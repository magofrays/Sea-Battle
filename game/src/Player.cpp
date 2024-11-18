#include "Player.h"

void Player::placeShipsRandomly(int single_decks, int double_decks, int three_decks, int four_decks){
    std::mt19937 gen(std::random_device{}());
    box2d field_area = play_field.getArea();
    point2d field_size = field_area.max_point;
    while(single_decks || double_decks || three_decks || four_decks){
        bool is_vertical = true;
        int x = gen()%field_size.x; 
        int y = gen()%field_size.y;
        int length;
        if(four_decks){
            length = 4;
        }
        else if(three_decks){
            length = 3;
        }
        else if(double_decks){
            length = 2;
        }
        else if(single_decks){
            length = 1;
        }
        bool placed = false;
        for(int i = 0; i != field_size.x+1; i++){
            for(int j = 0; j != field_size.y+1; j++){
                for(int changer = 0; changer != 2; changer++){
                    Ship ship(length, {(x+i)%(field_size.x+1), (y+j)%(field_size.y+1)}, (is_vertical && changer));
                    box2d ship_area = ship.getArea();
                    if(play_field.getArea().contains(ship_area) && !ship_manager.shipIntersection(ship_area)){
                        this->placeShip(std::make_shared<Ship>(ship));
                        switch(length){
                            case 4:
                                four_decks--;
                                break;
                            case 3:
                                three_decks--;
                                break;
                            case 2:
                                double_decks--;
                                break;
                            case 1:
                                single_decks--;
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
            if(placed) break;
        }
    }
}
