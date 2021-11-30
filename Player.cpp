#include "Player.h"

int Player::getPlayerID() const
{
    return playerID;
}

Group* Player::getGroupPointer() const
{
    return group;
}