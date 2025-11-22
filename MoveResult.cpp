#include "MoveResult.h"

MoveResult::MoveResult()		// always gives me a warning that it's uninitialized, not sure what the best way to fix it is
{
}

MoveResult::MoveResult(Tile* n)
{
	action = MoveResultAction::MoveOK;
	tile = n;
	character = nullptr;
}

MoveResult::~MoveResult()
{
	
}

Tile* MoveResult::GetTile()
{
	return nullptr;
}

void MoveResult::SetAction(MoveResultAction a)
{
}

MoveResultAction MoveResult::GetAction()
{
	return MoveResultAction();		// return default value?
}
