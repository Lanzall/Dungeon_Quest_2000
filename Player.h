#pragma once
#include "GameCharacter.h"
#include "Enums.h"
class Player :
    public GameCharacter
{
public:
	void Move(Direction dir, int dist);		// Lets the player move by a distance
};

