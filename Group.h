#ifndef _GROUP_H_
#define _GROUP_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Player.h"

class Group
{
    int IDNum;
    AVL_Tree<int, PlayerSeat> GroupPlayersTree;

public:
    Group(int GroupID) : IDNum(GroupID){};
    ~Group();

    int getID() const
    {
        return IDNum;
    }
    AVL_Tree<int, PlayerSeat> getPlayerTree() const
    {
        return GroupPlayersTree;
    }
};

#endif
