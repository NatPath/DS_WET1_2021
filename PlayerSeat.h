#ifndef _PlayerSeat_H_
#define _PlayerSeat_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Group.h"
#include "Player.h"

class PlayerSeat
{
    Player* player_on_seat;

public:

    PlayerSeat(Player* player_on_seat) : player_on_seat(player_on_seat){}
    /**
     * TODO:
     * 1)define operators <,>,<=,>=,==,!= (can look at Pair.h or Course.h in 2020 for reference)
     * 2)
     * 3)
     * */



};

#endif
