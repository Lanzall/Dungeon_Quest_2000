#pragma once
enum Direction {North, East, South, West, Unknown = -1};

static Direction OppositeDirection(Direction dir)		// returns the opposite direction
{
	if (dir == Direction::North) return Direction::South;
	else if (dir == Direction::East) return Direction::West;
	else if (dir == Direction::South) return Direction::North;
	else if (dir == Direction::West) return Direction::East;
}


enum MoveResultAction
{
	Undefined = -1,
	Blocked = 0,
	MoveOK = 1,
	Fight = 2,
	LoadNewRoom = 3
};

