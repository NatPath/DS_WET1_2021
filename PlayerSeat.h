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
    Player *player_on_seat;

public:
    PlayerSeat(Player *player_on_seat) : player_on_seat(player_on_seat) {}
    Player *getPlayerOnSeat() const;
    /**
     * TODO:
     * 1)define operators <,>,<=,>=,==,!= (can look at Pair.h or Course.h in 2020 for reference)
     * 2)
     * 3)
     * */

    friend bool operator<(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2);
    friend bool operator==(const PlayerSeat &player_seat_1, const PlayerSeat &player_seat_2);
};
void updatePlayerSeatAboutGroup(Node_ptr<PlayerSeat, PlayerSeat> player_seat, Group *group_p);

#endif
