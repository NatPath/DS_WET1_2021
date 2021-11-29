#ifndef _Player_H_
#define _Player_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Group.h"
#include "PlayerSeat.h"

class Player
{
    int playerID;
    int groupID;
    int level;
    PlayerSeat *Seat;

public:
    /***********************************************************
         * Player: constructor for Player
         * 
         * @param playerID the player's ID
         * @param groupID the player's Group ID
         * @param level the player's level
         ***********************************************************/
    Player(int playerID, int groupID, int level) : playerID(playerID), groupID(groupID), level(level) {}

    
};

#endif
