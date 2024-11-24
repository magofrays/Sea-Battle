#include "Player.h"

class botPlayer: public Player{
    public:
    void Attack();
    void setField(playField play_field);
    void getOpponent(Player * player);
    
};