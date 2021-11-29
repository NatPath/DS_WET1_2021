#ifndef _GROUP_H_
#define _GROUP_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Player.h"

class PlayerSeat{
    Player* player;
    public:
    bool operator<(const Player& player);
};
class Group
{
    int group_id;
    int size;
    AVL_Tree<PlayerSeat, PlayerSeat> GroupPlayersTree;
    Node_ptr<PlayerSeat,PlayerSeat> highest_level_player;

public:
    Group(int groupID) : group_id(groupID){};
    ~Group();

    int getID() const
    {
        return group_id;
    }
    AVL_Tree<PlayerSeat, PlayerSeat> getPlayerTree() const{
        return GroupPlayersTree;
    }
    //gets the size of the group
    int getSize() const;

    void insertPlayer(Player* player_p);

};

#endif
