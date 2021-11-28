#ifndef _OCTOPUSGAME_H_
#define _OCTOPUSGAME_H_
#include <memory>
#include <exception>
#include "Auxiliaries.h"
#include "library1.h"
#include "Avl.h"
#include "Player.h"

class Group
{
    int IDNum;
    AVL_Tree GroupPlayersTree;
    
public:
    Group(int GroupID);
    ~Group();
};