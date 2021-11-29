#include "OctopusGame.h"

////////////////////////////////// private functions implementation //////////////////////////////////
void OctopusGame::addPlayerToGroup(Player* player_p, Group* group_p){
    if (group_p->getSize()==0){
        NonEmptyGroupsTree.insertNode(group_p->getID(),group_p);
    }
    group_p->insertPlayer(player_p);
    player_p->setGroup(group_p);

}

////////////////////////////////// public functions implementation //////////////////////////////////

StatusType OctopusGame::AddGroup(int GroupID)
{
    try
    {
        Group group_to_add(GroupID); 

        if (GroupTree.insertNode(GroupID, group_to_add) == false) // Check if group already exists
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
        Player new_player(PlayerID, GroupID, Level);

        // Adding Player to player by ID tree

        if (PlayerByIDTree.insertNode(PlayerID, new_player) == false)
        {
            return FAILURE;
        }

        Node_ptr<int,Group> group_node = GroupTree.findLastOfSearchPath(GroupID);
        if (group_node == nullptr) // Should maybe add "group_to_add_player == nullptr"
        {
            return FAILURE;
        }

        PlayerSeat player_seat(&new_player);
        PlayerByLevelTree.insertNode(player_seat,player_seat);

        Group* group_p= &(group_node->getValue());

        // Adding Player to a group
        addPlayerToGroup(&new_player,group_p);

        return SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType OctopusGame::RemovePlayer(int PlayerID)
{
    //find player in playersByIdTree
    Player* player_p_to_remove = &((PlayerByIDTree.findLastOfSearchPath(PlayerID))->getValue());//you might ask why we need all this pointer stuff.. the reason is to avoid copying stuff when not needed
    
    //check for errors
    if(...){
        return StatusType::FAILURE;
    }

    //use player_p to get to its group and update the group O(1)

    //check if we need to remove the group from the nonemptytree 
    //if so
    //find the group key in the nonemptytree in O(logn). use a fake PlayerSeat to do so.
    //delete the group with the found key from the nonemptytree.

    //remove from PlayerByIdTree

    //remove from PlayerByLevelTree



    return StatusType::SUCCESS;    
}
