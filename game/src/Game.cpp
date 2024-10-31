#include "Game.h"

void Game::Setup(){
    om.update();
    while(true){
    try{
        om.drawMessage("Input Field. Format:\nw h(width, height)\n");
        point2d size;
        im.inputCoordinates(size);
        playField new_field(size);
        player.play_field = new_field;
        break;
        }
        catch(invalidFieldSize & e){
            om.drawMessage(e.what());
        }
        catch(inputException & e){
            om.drawMessage(e.what());
        }
    }
    om.update();
    for(int i = 0; i != 5; ++i){
        om.drawField(player.play_field, false);
        player.placeShip();
    }
}

void Game::Play(){
    player.getOpponent(&player);
    while(true){
        
        
        char c;
        while(true){
            try{
                om.drawField(*(player.opponent_play_field), true);
                om.drawMessage("Choose action:\nu - use ability, then attack\na - attack\n");
                im.inputAction(c);
                break;
                }
            catch(inputException & e){
                om.update();
                om.drawMessage(e.what());
            }
        }
        om.update();
        om.drawField(*(player.opponent_play_field), true);
        switch(c){
            case 'u':
                player.useAbility();
            case 'a':
                om.drawMessage("Input coordinates for Attack\n");
                player.Attack();
        }
        if(player.opponent_ship_manager->allShipsDestroyed()){
            break;
        }
    }
    om.update();
    om.drawMessage("All ships destroyed!\n");
    om.drawField(*(player.opponent_play_field), false);
}