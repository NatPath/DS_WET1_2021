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
    int PlayerID;
    int GroupID;
    int Level;
    PlayerSeat* Seat;

};

#endif
