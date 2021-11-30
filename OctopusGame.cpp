#include "OctopusGame.h"

////////////////////////////////// private functions implementation //////////////////////////////////
void OctopusGame::addPlayerToGroup(Player *player_p, Group *group_p)
{
    if (group_p->getSize() == 0)
    {
        NonEmptyGroupsTree.insertNode(group_p->getID(), group_p);
    }
    group_p->insertPlayer(player_p);
    player_p->setGroup(group_p);
}
void OctopusGame::updateGlobalBestPlayer(){
    int num_of_players= PlayerByLevelTree.getNumNodes();
    Node_ptr<PlayerSeat,PlayerSeat> playerseat = PlayerByLevelTree.select(num_of_players);
    GlobalBestPlayer = (playerseat->getValue()).getPlayerOnSeat();
}

////////////////////////////////// public functions implementation //////////////////////////////////

StatusType OctopusGame::AddGroup(int GroupID)
{
    try
    {
        Group group_to_add(GroupID);

        if (GroupTree.insertNode(GroupID, group_to_add) == false) // Check if group already exists
        {
            return StatusType::FAILURE;
        }
        return SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
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
            return StatusType::FAILURE;
        }

        Node_ptr<int, Group> group_node = GroupTree.findLastOfSearchPath(GroupID);
        if (group_node == nullptr) // Should maybe add "group_to_add_player == nullptr"
        {
            return StatusType::FAILURE;
        }

        // Adding Player to player by ID tree

        PlayerSeat player_seat(&new_player);
        PlayerByLevelTree.insertNode(player_seat, player_seat);
        updateGlobalBestPlayer();

        Group *group_p = &(group_node->getValue());

        // Adding Player to a group
        addPlayerToGroup(&new_player, group_p);

        return SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType OctopusGame::RemovePlayer(int PlayerID)
{
    //find player in playersByIdTree
    Node_ptr<int, Player> player_to_remove_node = PlayerByIDTree.findLastOfSearchPath(PlayerID);
    if (player_to_remove_node == nullptr)
    {
        return StatusType::FAILURE;
    }

    Player *player_p_to_remove = &(player_to_remove_node->getValue()); //you might ask why we need all this pointer stuff.. the reason is to avoid copying stuff when not needed
    //check for errors
    if (player_p_to_remove->getPlayerID() != PlayerID)
    {
        return StatusType::FAILURE;
    }

    //use player_p to get to its group O(1)
    Group *player_group_p = player_p_to_remove->getGroupPointer();

    PlayerSeat player_to_remove_seat(player_p_to_remove);

    //check if we need to remove the group from the nonemptytree
    //if so
    //find the group key in the nonemptytree in O(logn) and remove it at O(1)
    //delete the group with the found key from the nonemptytree.
    
    if (player_group_p->getSize() == 1)
    {
        NonEmptyGroupsTree.deleteNode(player_group_p->getID()); // Need to check at debugging that Add player inserts Group Pointer correctly to NonEmptyGroupsTree, may cause bugs.
    }
    player_group_p->setSize(player_group_p->getSize() - 1);
    AVL_Tree<PlayerSeat, PlayerSeat>& player_to_remove_group_tree = player_group_p->getPlayerTree(); // need to verify assignment operator of AVL. May cause bugs.
    player_to_remove_group_tree.deleteNode(player_to_remove_seat);
    player_group_p->updateHighestLevelPlayer();

    //remove from PlayerByLevelTree , use a fake PlayerSeat to do so. O(logn)
    PlayerByLevelTree.deleteNode(player_to_remove_seat);
    updateGlobalBestPlayer();

    //remove from PlayerByIdTree O(logn)
    PlayerByIDTree.deleteNode(PlayerID);
    



    return StatusType::SUCCESS;
}

StatusType OctopusGame::ReplaceGroup(int GroupID, int ReplacementID)
{
    try
    {

        //return Failure if there isn't a group with GroupId or ReplacementId
        Node_ptr<int, Group> group_node_to_replace = GroupTree.findLastOfSearchPath(GroupID);
        Node_ptr<int, Group> replacement_group_node = GroupTree.findLastOfSearchPath(ReplacementID);
        if (group_node_to_replace == nullptr || replacement_group_node == nullptr)
        {
            return StatusType::FAILURE;
        }

        Group *group_p_to_replace = &(group_node_to_replace->getValue());
        Group *replacement_group_p = &(replacement_group_node->getValue());
        AVL_Tree<PlayerSeat, PlayerSeat> tree_to_replace = group_p_to_replace->getPlayerTree();
        AVL_Tree<PlayerSeat, PlayerSeat> replacement_tree = replacement_group_p->getPlayerTree();

        //make a merged group
        AVL_Tree<PlayerSeat, PlayerSeat> merged_tree = merge_trees(tree_to_replace, replacement_tree);
        Group merged_group(ReplacementID);
        merged_group.setGroupsPlayerTree(merged_tree);
        int group_to_replace_size = group_p_to_replace->getSize();
        int replacement_group_size = replacement_group_p->getSize();
        int merged_group_size = group_to_replace_size + replacement_group_size;
        merged_group.setSize(merged_group_size);
        merged_group.updateHighestLevelPlayer();
        //update all the groups players about their new group
        merged_group.updateGroupPlayersAboutGroup();

        //delete old groups
        bool to_replace_empty = (group_p_to_replace == 0);
        bool replacement_empty = (group_to_replace_size == 0);
        GroupTree.deleteNode(GroupID);
        if (to_replace_empty)
        {
            NonEmptyGroupsTree.deleteNode(GroupID);
        }
        GroupTree.deleteNode(ReplacementID);
        if (replacement_empty)
        {
            NonEmptyGroupsTree.deleteNode(ReplacementID);
        }

        //insert merged group
        GroupTree.insertNode(ReplacementID, merged_group);
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

    //
}

StatusType OctopusGame::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    try
    {

        //remove player

        //insert player with the level increased
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}
StatusType OctopusGame::GetHighestLevel(int GroupID, int *PlayerID)
{

    //return the fitting field in Group/PlayerByLevelTree
}

StatusType OctopusGame::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    try
    {
        // numOfPlayer <-- fitting field in group/Players_tree_size
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType OctopusGame::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    try
    {
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

void OctopusGame::Quit()
{
}
