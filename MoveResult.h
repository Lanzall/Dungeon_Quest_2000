#pragma once
#include "Tile.h"
#include "GameCharacter.h"
#include "enums.h"

class MoveResult
{
public:
	MoveResult();
	MoveResult(Tile* n);
	~MoveResult();
	Tile* GetTile();
	void SetAction(MoveResultAction a);
private:
	MoveResultAction action;
	GameCharacter* character;
	Tile* tile;
};

