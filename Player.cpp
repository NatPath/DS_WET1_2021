#include "Player.h"

int Player::getPlayerID() const
{
    return playerID;
}

Group *Player::getGroupPointer() const
{
    return group;
}


int Player::getLevel()
{
    return level;
}

void Player::setGroup(Group *new_group_p){
    group=new_group_p;
    groupID=new_group_p->getID();
}

void Player::setLevel(int new_level)
{
    level = new_level;
}
