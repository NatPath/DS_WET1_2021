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
void OctopusGame::updateGlobalBestPlayer()
{
    int num_of_players = PlayerByLevelTree.getNumNodes();
    Node_ptr<PlayerSeat, PlayerSeat> playerseat = PlayerByLevelTree.select(num_of_players);
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
    return StatusType::FAILURE;
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

        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;

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
    AVL_Tree<PlayerSeat, PlayerSeat> &player_to_remove_group_tree = player_group_p->getPlayerTree(); // need to verify assignment operator of AVL. May cause bugs.
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
        if (group_p_to_replace->getID() != GroupID || replacement_group_p->getID() != ReplacementID){
            return StatusType::FAILURE;
        }
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
    return StatusType::FAILURE;
    //
}

StatusType OctopusGame::IncreaseLevel(int PlayerID, int LevelIncrease)
{
    try
    {

        Node_ptr<int, Player> player_to_increase_level_node = PlayerByIDTree.findLastOfSearchPath(PlayerID);
        if (player_to_increase_level_node == nullptr)
        {
            return StatusType::FAILURE;
        }

        Player *player_to_increase_level = &(player_to_increase_level_node->getValue()); //you might ask why we need all this pointer stuff.. the reason is to avoid copying stuff when not needed
        //check for errors
        if (player_to_increase_level->getPlayerID() != PlayerID)
        {
            return StatusType::FAILURE;
        }

        Group *player_group_p = player_to_increase_level->getGroupPointer();
        AVL_Tree<PlayerSeat, PlayerSeat> &player_to_increase_level_group_tree = player_group_p->getPlayerTree(); // need to verify assignment operator of AVL. May cause bugs.
        PlayerSeat player_to_increase_level_seat(player_to_increase_level);
        player_to_increase_level_group_tree.deleteNode(player_to_increase_level_seat);
        player_to_increase_level->setLevel(player_to_increase_level->getLevel() + LevelIncrease);
        player_to_increase_level_group_tree.insertNode(player_to_increase_level_seat, player_to_increase_level_seat);
        player_group_p->updateHighestLevelPlayer();
        PlayerByLevelTree.deleteNode(player_to_increase_level_seat);
        PlayerByLevelTree.insertNode(player_to_increase_level_seat, player_to_increase_level_seat);

        updateGlobalBestPlayer();

        //remove player

        //insert player with the level increased
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}
StatusType OctopusGame::GetHighestLevel(int GroupID, int *PlayerID)
{
    if (GroupID<0){
        if (GlobalBestPlayer==nullptr){//there are no players
            *PlayerID=1;
            return StatusType::SUCCESS;
        }
        *PlayerID = GlobalBestPlayer->getPlayerID();
        return StatusType::SUCCESS;
    }   
    Node_ptr<int,Group> found_node = GroupTree.findLastOfSearchPath(GroupID);
    Group& found_group = found_node->getValue();
    if (found_group.getID() != GroupID){// the group is not in the tree
        return StatusType::FAILURE;
    }
    Node_ptr<PlayerSeat,PlayerSeat> highest_player_in_group =found_group.getHighestLevelPlayer();
    *PlayerID = highest_player_in_group->getValue().getPlayerOnSeat()->getPlayerID();
    return StatusType::SUCCESS;

}

StatusType OctopusGame::GetAllPlayersByLevel(int GroupID, int **Players, int *numOfPlayers)
{
    try
    {
        if(GroupID<0){
            Node_ptr<PlayerSeat,PlayerSeat> playbylevel_root=PlayerByLevelTree.getRoot();
            int index=0;
            if (playbylevel_root==nullptr){//no players
                *numOfPlayers=0;
                *Players=nullptr;
                return StatusType::SUCCESS;
            }
            int num_of_players = playbylevel_root->getRank();
            DynamicArray<Pair<PlayerSeat,PlayerSeat>> arr(num_of_players);
            Node_ptr<PlayerSeat,PlayerSeat> global_highest_level_player_node= PlayerByLevelTree.select(num_of_players);
            reverseClimbTreeFromRight(global_highest_level_player_node,true,true,true,&index,arr,num_of_players);
            *numOfPlayers=num_of_players;
            Players = (int**)malloc(num_of_players*sizeof(int*));
            for (int i=0; i<num_of_players;i++){
                (*Players)[i]=(arr[i].getValue().getPlayerOnSeat())->getPlayerID();
            }
            return StatusType::SUCCESS;
        }
        Node_ptr<int,Group> found_group_node= GroupTree.findLastOfSearchPath(GroupID);
        if (found_group_node==nullptr){// there are no groups 
            return StatusType::FAILURE;
        }
        Group& found_group = found_group_node->getValue();
        if (found_group.getID() != GroupID){// group does not exist
            return StatusType::FAILURE;
        }
        Node_ptr<PlayerSeat,PlayerSeat> players_in_group_tree_root= found_group.getPlayerTree().getRoot();
        int num_of_group_players = players_in_group_tree_root->getRank();
        DynamicArray<Pair<PlayerSeat,PlayerSeat>> arr(num_of_group_players);
        int index=0;
        Node_ptr<PlayerSeat,PlayerSeat> highest_level_in_group_node = found_group.getHighestLevelPlayer();
        reverseClimbTreeFromRight(highest_level_in_group_node,true,true,true,&index,arr,num_of_group_players);
        *numOfPlayers=num_of_group_players;
        Players = (int**)malloc(num_of_group_players*sizeof(int*));
        for (int i=0; i<num_of_group_players; i++){
            (*Players)[i]=(arr[i].getValue().getPlayerOnSeat())->getPlayerID();
        }
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}

StatusType OctopusGame::GetGroupsHighestLevel(int numOfGroups, int **Players)
{
    try
    {
        Node_ptr<int,Group*> non_empty_group_tree_root = NonEmptyGroupsTree.getRoot();
        if (non_empty_group_tree_root==nullptr){ //there are 0 nonempty groups
            return StatusType::FAILURE;
        }
        int num_of_non_empty_groups = non_empty_group_tree_root->getRank();
        if (num_of_non_empty_groups< numOfGroups){
            return StatusType::FAILURE;
        }
        Node_ptr<int,Group*> smallest_id_non_empty_group_node = NonEmptyGroupsTree.select(1);
        int index=0;
        DynamicArray<Pair<int,Group*>> arr(numOfGroups);
        reverseClimbTreeFromLeft(smallest_id_non_empty_group_node,true,true,true,&index,arr,numOfGroups);
        Players = (int**)malloc(numOfGroups*sizeof(int*));
        for (int i=0 ; i<numOfGroups; i++){
            Node_ptr<PlayerSeat,PlayerSeat> highest_level_player_in_group_node= (arr[i].getValue())->getHighestLevelPlayer();
            Player* highest_level_player_in_group = (highest_level_player_in_group_node->getValue()).getPlayerOnSeat();
            (*Players)[i] = highest_level_player_in_group->getPlayerID();
        }
        return StatusType::SUCCESS;
    }
    catch (const std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::FAILURE;
}
