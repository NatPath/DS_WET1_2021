#ifndef _OCTOPUSGAME_H_
#define _OCTOPUSGAME_H_
#include <memory>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Group.h"
#include "Player.h"

class OctopusGame
{

    AVL_Tree<int, Player> PlayerByIDTree;
    AVL_Tree<int, Player> PlayerByLevelTree;
    AVL_Tree<int, Group> GroupTree;
    AVL_Tree<int, Group> NonEmptyGroupsTree;
    Player GlobalBestPlayer;

public:
    OctopusGame() = default;

    ~OctopusGame() = default;
    StatusType AddGroup(int GroupID);

    StatusType AddPlayer(int PlayerID, int GroupID, int Level);

    StatusType RemovePlayer(int PlayerID);

    StatusType ReplaceGroup(int GroupID, int ReplacementID);

    StatusType IncreaseLevel(int PlayerID, int LevelIncrease);

    StatusType GetHighestLevel(int GroupID, int *PlayerID);

    StatusType GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers);

    StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);
};

#endif
