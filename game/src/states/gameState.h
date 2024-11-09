#include "../messages/messageHandler.h"
class Game;
class gameState: public messageHandler{
    messageHandler * handler;
    protected:
        Game & game; 
    public:
        void setGame(Game & game){
            this->game = game;
        }
        virtual void execute() = 0;
        virtual ~gameState() {}

        template <typename T>
        virtual void Handle(Message<T> message) = 0;
        void setNext(messageHandler * handler){
            this->handler = handler;
        }
};