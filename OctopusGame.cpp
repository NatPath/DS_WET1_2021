#include "OctopusGame.h"

////////////////////////////////// private functions implementation //////////////////////////////////

////////////////////////////////// public functions implementation //////////////////////////////////

StatusType OctopusGame::AddGroup(int GroupID)
{
    try
    {
        Group group_to_add = Group(GroupID)

            if (GroupTree.insertNode(GroupID, group_to_add) == 0)
        {
            return FAILURE;
        }
        return SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType AddPlayer(int PlayerID, int GroupID, int Level)
{
    try
    {
        Group group_to_add_player = (GroupTree.findLastOfSearchPath(GroupID))->getValue();
        if (group_to_add_player.IDNum == nullptr || group_to_add_player.IDNum != GroupID)
        {
            return FAILURE;
        }
        
        if (GroupTree.insertNode(GroupID, group_to_add) == 0 || )
        {
            return FAILURE;
        }
        return SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }

}
