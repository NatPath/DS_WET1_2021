#include "library1.h"
#include "OctopusGame.h"

void *Init()
{
    OctopusGame *DS = new OctopusGame();
    return (void *)DS;
}


StatusType AddGroup(void *DS, int GroupID)
{
    if (DS == nullptr || GroupID <= 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->AddGroup(GroupID); // Needs to take care of StatusType -ALLOCATION_ERROR, Failure and Success
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level)
{
    if (DS == nullptr || GroupID <= 0 || PlayerID <= 0 || Level < 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->AddPlayer(PlayerID, GroupID, Level); // Needs to take care of StatusType -ALLOCATION_ERROR, Failure and Success
}

StatusType RemovePlayer(void *DS, int PlayerID, int GroupID, int Level)
{
    if (DS == nullptr || PlayerID <= 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->RemovePlayer(PlayerID, GroupID); // Needs to take care of StatusType -ALLOCATION_ERROR, Failure and Success
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID)
{
    if (DS == nullptr || GroupID <= 0 || ReplacementID <= 0 || GroupID == ReplacementID)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->ReplaceGroup(GroupID, ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (DS == nullptr || PlayerID <= 0 || LevelIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->IncreaseLevel(PlayerID, LevelIncrease);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (DS == nullptr || PlayerID <= 0 || LevelIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->ReplaceGroup(PlayerID, LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID)
{
    if (DS == nullptr || PlayerID == nullptr || GroupID == 0)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->GetHighestLevel(GroupID, PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers)
{
    if (DS == nullptr || GroupID == 0 || *Players == nullptr || numOfPlayers = nullptr)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->GetHighestLevel(GroupID, *Players, numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players)
{
    if (DS == nullptr || numOfGroups <1 || *Players == nullptr)
    {
        return INVALID_INPUT;
    }
    OctopusGame *Ogame = static_cast<OctopusGame *>(DS);
    return (Ogame)->GetHighestLevel(numOfGroups, *Players);
}

void Quit(void** DS){
    delete (OctopusGame*)(*DS);
}
