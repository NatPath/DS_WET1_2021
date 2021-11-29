#include "OctopusGame.h"

////////////////////////////////// private functions implementation //////////////////////////////////

////////////////////////////////// public functions implementation //////////////////////////////////

StatusType OctopusGame::AddGroup(int GroupID)
{
    try
    {
        Group group_to_add = Group(GroupID);

        if (GroupTree.insertNode(GroupID, group_to_add) == 0) // Check if group already exists
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

StatusType OctopusGame::AddPlayer(int PlayerID, int GroupID, int Level)
{
    try
    {
        Player new_player = Player(PlayerID, GroupID, Level);

        // Adding Player to player by ID tree

        if (PlayerByIDTree.insertNode(PlayerID, new_player) == 0)
        {
            return FAILURE;
        }

        // Adding Player to player by level tree

        // if (PlayerByIDTree.insertNode(PlayerID, new_player) == 0)
        // {
        //     return FAILURE;
        // }

        // Adding Player to a group

        Group group_to_add_player = (GroupTree.findLastOfSearchPath(GroupID))->getValue();

        if (&group_to_add_player == nullptr || group_to_add_player.getID() != GroupID) // Should maybe add "group_to_add_player == nullptr"
        {
            return FAILURE;
        }
        PlayerSeat new_player_seat = PlayerSeat(&new_player);

        if ((group_to_add_player.getPlayerTree()).insertNode(PlayerID, new_player_seat) == 0) // Player is already in the group.
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

StatusType OctopusGame::RemovePlayer(int PlayerID)
{
    Player player_to_remove = (PlayerByIDTree.findLastOfSearchPath(PlayerID))->getValue();

    if (/* condition */)
    {
        /* code */
    }
    
}
