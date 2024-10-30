#include "Game.h"

void Game::Setup(){
    om.update();
    while(true){
    try{
        om.drawMessage("Input Field. Format:\nw h(width, height)\n");
        im.inputPlayField(player.play_field);
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
    
    player.getOpponent(&player.play_field, &player.ship_manager);
    while(true){
        
        om.drawField(*(player.opponent_play_field), true);
        om.drawMessage("Choose action:\nu - use ability, then attack\na - attack\n");
        char c;
        while(true){
            try{
                im.inputAction(c);
                break;
                }
            catch(inputException & e){
                om.drawMessage(e.what());
            }
        }
        switch(c){
            case 'u':
                player.useAbility();
            case 'a':
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