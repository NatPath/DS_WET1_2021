#include "Group.h"

int Group::getSize() const{
    return size;
}
void Group::insertPlayer(Player* player_p){
    PlayerSeat player_seat(player_p);
    GroupPlayersTree.insertNode(player_seat,player_seat);
    size++;
    highest_level_player= GroupPlayersTree.select(size);
}