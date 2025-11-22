#include "Player.h"


void Player::Move(Direction dir, int dist)
{
	// Movement related, just moves the player with the rect by the distance in the direction
	if (dir == Direction::North)
	{
		Rect.y -= dist;
	}
	else if (dir == Direction::East)
	{
		Rect.x += dist;
	}
	else if (dir == Direction::South)
	{
		Rect.y += dist;
	}
	else if (dir == Direction::West)
	{
		Rect.x -= dist;
	}

}