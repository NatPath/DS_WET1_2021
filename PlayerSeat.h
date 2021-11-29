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
    Player* Player_on_seat;

public:

    PlayerSeat(Player* Player_on_seat) : Player_on_seat(Player_on_seat){}


};

#endif
